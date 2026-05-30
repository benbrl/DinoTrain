#include "draw_scene.hpp"
#include "utilsJson.hpp"
#include "draw_train.hpp"
#include "draw_rail_droite.hpp"
#include "draw_rail_courbe.hpp"

/// Camera parameters
float angle_theta{45.0}; // Angle between x axis and viewpoint
float angle_phy{30.0};	 // Angle between z axis and viewpoint
float dist_zoom{10.0};	 // Distance between origin and viewpoint

GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
GLBI_Convex_2D_Shape ground{3};
GLBI_Convex_2D_Shape ground_debug{3};
GLBI_Convex_2D_Shape RailInt;
GLBI_Convex_2D_Shape carre;

IndexedMesh *sphere = NULL;
IndexedMesh *balast = NULL;
IndexedMesh *rail = NULL;
IndexedMesh *cercle = NULL;
IndexedMesh *cube = NULL;
IndexedMesh *cylindre = NULL;
StandardMesh *cone = NULL;

MatrixStack modelviewStack;

GLBI_Set_Of_Points grid_pts(3);

const float axe_x{10.0f};
const float axe_y{10.0f};

const float sx{0.75};
// a verifier le sr j n'ai pas vu le chiffre donc j'ai mis arbitrairement 0.5
const float sr{0.5f};
const float rr{0.5f};
const int POS_X_RAIL1{3};
const int POS_X_RAIL2{7};
const float rayon_rail_fer{sr / 2};
const float rayon_rail_balast{rr / 2};

Vector3D z_axe{0.0f, 0.0f, 1.0f};
Vector3D y_axe{0.0f, 1.0f, 0.0f};
Vector3D x_axe{1.0f, 0.0f, 0.0f};

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

	cercle = basicSphere(1.0f, 64, 64);
	cercle->createVAO();

	cone = basicCone(1.0f, 1.0f);
	cone->createVAO();

	cube = basicCube(1.0f);
	cube->createVAO();
	// Rail courbé 2D

	cylindre = basicCylinder(1.0f, 1.0f, 16, 4);
	cylindre->createVAO();

	std::vector<float> railIntPoints;
	int nbPoints = 100;
	float angleStep = (M_PI / 2.0f) / nbPoints;

	for (int i = 0; i <= nbPoints; i++)
	{
		float angle = i * angleStep;
		// intérieur de la bande
		railIntPoints.push_back((POS_X_RAIL1 - sr / 2) * cos(angle));
		railIntPoints.push_back((POS_X_RAIL1 - sr / 2) * sin(angle));

		// extérieur de la bande
		railIntPoints.push_back((POS_X_RAIL1 + sr / 2) * cos(angle));
		railIntPoints.push_back((POS_X_RAIL1 + sr / 2) * sin(angle));
	}
	RailInt.initShape(railIntPoints);
	RailInt.changeNature(GL_TRIANGLE_STRIP);

	// carré

	std::vector<float> carre_points{1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f};

	carre.initShape(carre_points);
	carre.changeNature(GL_TRIANGLE_FAN);
}

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

Vector3D z_axe{0.0f, 0.0f, 1.0f};
Vector3D y_axe{0.0f, 1.0f, 0.0f};
Vector3D x_axe{1.0f, 0.0f, 0.0f};

void drawRailFerCourbe()
{
	// Dessous
	myEngine.mvMatrixStack.pushMatrix();
	// myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, z_axe);
	Vector3D trans3{0.0f, 0.0f, rr};
	myEngine.mvMatrixStack.addTranslation(trans3);
	myEngine.setFlatColor(0.749, 0.788, 0.82);
	myEngine.updateMvMatrix();
	RailInt.drawShape();

	// Dessus
	Vector3D trans4{0.0f, 0.0f, sr};
	myEngine.mvMatrixStack.addTranslation(trans4);
	myEngine.updateMvMatrix();
	RailInt.drawShape();
	myEngine.mvMatrixStack.popMatrix();

	// carré x
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, POS_X_RAIL1 - sr / 2.0f, rr));
	myEngine.mvMatrixStack.addRotation(-M_PI / 2.0f, y_axe);
	myEngine.mvMatrixStack.addHomothety(Vector3D(sr, sr, 1.0f));
	myEngine.updateMvMatrix();
	carre.drawShape();
	myEngine.mvMatrixStack.popMatrix();

	// carré y
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(POS_X_RAIL1 - sr / 2.0f, 0.0f, 2 * rr));
	myEngine.mvMatrixStack.addRotation(-M_PI / 2.0f, x_axe);
	myEngine.mvMatrixStack.addHomothety(Vector3D(sr, sr, 1.0f));
	myEngine.updateMvMatrix();
	carre.drawShape();
	myEngine.mvMatrixStack.popMatrix();

	// milieu
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0, sr));

	int nbPoints = 100;
	float angleStep = (M_PI / 2.0f) / nbPoints;

	for (int i = 0; i <= nbPoints; i++)
	{
		float angle = i * angleStep;
		myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addTranslation(Vector3D((POS_X_RAIL1 - sr / 2) * cos(angle), (POS_X_RAIL1 - sr / 2) * sin(angle), 0.0f));
		// myEngine.mvMatrixStack.addRotation(angle+M_PI/2.0f, z_axe);	// pour faire forme en 3D
		myEngine.mvMatrixStack.addRotation(angle, z_axe);
		myEngine.mvMatrixStack.addRotation(-M_PI / 2.0f, y_axe);
		myEngine.mvMatrixStack.addHomothety(Vector3D(sr, sr, 1.0f));
		myEngine.updateMvMatrix();
		carre.drawShape();
		myEngine.mvMatrixStack.popMatrix();
	}

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

void drawRailCourbe()
{
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation(-M_PI / 2, z_axe);

	// Les 3 balast
	myEngine.mvMatrixStack.pushMatrix();
	float angle = M_PI / 6;
	myEngine.mvMatrixStack.addRotation(M_PI / 12, z_axe);

	for (int i = 0; i < 3; ++i)
	{
		myEngine.mvMatrixStack.pushMatrix();
		myEngine.mvMatrixStack.addRotation(angle * i, z_axe);
		Vector3D trans2{0.0f, 2.0f, 0.0f};
		myEngine.mvMatrixStack.addTranslation(trans2);
		drawBalast();

		myEngine.mvMatrixStack.popMatrix();
	}
	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.popMatrix();

	// rail courbé int
	myEngine.mvMatrixStack.pushMatrix();
	drawRailFerCourbe();
	myEngine.mvMatrixStack.popMatrix();
}

void drawScene()
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

	// drawRailFer();
	// drawBalast();
	// drawRailDroite();
	// drawRailCourbe();
	// drawRailFerCourbe();
	// drawRailDroite_position(0, 1);

	// drawTrain();

	//  moteur();
	rail_type_detect(config);
	// draw_dino();
}
