#include "draw_scene.hpp"
#include "utilsJson.hpp"

/// Camera parameters
float angle_theta{45.0}; // Angle between x axis and viewpoint
float angle_phy{30.0};	 // Angle between z axis and viewpoint
float dist_zoom{30.0};	 // Distance between origin and viewpoint

GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
GLBI_Convex_2D_Shape ground{3};
GLBI_Convex_2D_Shape ground_debug{3};

MatrixStack modelviewStack;
IndexedMesh *sphere = NULL;
IndexedMesh *balast = NULL;
IndexedMesh *rail = NULL;

void initScene()
{
	std::vector<float> points{0.0, 0.0, 0.0};
	somePoints.initSet(points, 1.0, 1.0, 1.0);

	std::vector<float> baseCarre{-100.0, -100.0, 0.0,
								 100.0, -100.0, 0.0,
								 100.0, 100.0, 0.0,
								 -100.0, 100.0, 0.0};
	ground.initShape(baseCarre);
	ground.changeNature(GL_TRIANGLE_FAN);

	// debug
	std::vector<float> carreDebug{
		0.0, 10.0, 0.11,
		10.0, 10.0, 0.11,
		10.0, 0.0, 0.11,
		0.0, 0.0, 0.11};

	ground_debug.initShape(carreDebug);
	ground_debug.changeNature(GL_TRIANGLE_FAN);

	balast = basicCylinder(1.0f, 1.0f);
	balast->createVAO();

	rail = basicCube(1.0f);
	rail->createVAO();

	sphere = basicSphere(1.0f);
	sphere->createVAO();
}

const float axe_x{10.0f};
const float axe_y{10.0f};

const float sx{0.75};
// a verifier le sr j n'ai pas vu le chiffre donc j'ai mis arbitrairement 0.5
const float sr{0.5f};
const float rr{0.5f};

const int POS_X_RAIL1{3};
const int POS_X_RAIL2{7};

const float rayon_rail_fer = (sr / 2);
const float rayon_rail_balast = (rr / 2);

void drawBalast()
{

	myEngine.mvMatrixStack.pushMatrix(),
		myEngine.mvMatrixStack.addHomothety(Vector3D(rayon_rail_balast, axe_y - 4, rayon_rail_balast));
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0, rayon_rail_balast + rr));
	myEngine.updateMvMatrix();
	myEngine.setFlatColor(0.549, 0.353, 0.235);
	balast->draw();

	myEngine.mvMatrixStack.popMatrix();
}

void drawRailFer()
{

	myEngine.mvMatrixStack.pushMatrix(),
		myEngine.mvMatrixStack.addHomothety(Vector3D(sr / 2, axe_y, sr / 2));

	myEngine.updateMvMatrix();
	myEngine.setFlatColor(0.749, 0.788, 0.82);
	rail->draw();

	myEngine.mvMatrixStack.popMatrix();
}

void drawRailDroite()
{

	// premier

	for (int i = 0; i < 5; ++i)
	{
		myEngine.mvMatrixStack.pushMatrix();

		myEngine.mvMatrixStack.addTranslation(Vector3D(sx + i * (2.0f * sx + rr), 2.0f, 0));

		drawBalast();

		myEngine.mvMatrixStack.popMatrix();
	}

	// rail fer droite
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation(deg2rad(90), Vector3D(0.0, 0.0, 1.0));
	// myEngine.mvMatrixStack.addTranslation(Vector3D(POS_X_RAIL1, -axe_y / 2 + sx * 2, rr));
	myEngine.mvMatrixStack.addTranslation(Vector3D(POS_X_RAIL1, -axe_y / 2 + sx / 4, rr));
	drawRailFer();
	myEngine.mvMatrixStack.popMatrix();

	// rail fer gauche

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation(deg2rad(90), Vector3D(0.0, 0.0, 1.0));
	myEngine.mvMatrixStack.addTranslation(Vector3D(POS_X_RAIL2, -axe_y / 2 + sx / 4, rr));
	drawRailFer();
	myEngine.mvMatrixStack.popMatrix();
}

// WIP mettre float/int rotation apres
void drawRailDroite_position(int x, int y)
{
	std::cout << "---------------- position rails ---------------" << std::endl;

	std::cout << x << std::endl;
	std::cout << y << std::endl;

	myEngine.mvMatrixStack.pushMatrix();

	myEngine.mvMatrixStack.addTranslation(Vector3D(y * 10, x * 10, 0));

	drawRailDroite();

	myEngine.mvMatrixStack.popMatrix();
}

void drawScene(GridConfig config)
{
	glPointSize(10.0);

	somePoints.drawSet();

	myEngine.setFlatColor(0.435, 0.812, 0.592);
	ground.drawShape();

	myEngine.setFlatColor(1, 0.984, 0);
	ground_debug.drawShape();
	myEngine.setFlatColor(0.2, 1.0, 0.8);

	rail_type_detect(config);

	//  drawBalast();
	// drawRailDroite();
	// drawRailDroite_position(0, 1);
	// drawRailDroite_position(0, 0);
	// drawRailDroite_position(0, -1);
	// drawRailDroite_position(0, -2);
}
