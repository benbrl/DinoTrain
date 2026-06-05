#include "draw_scene.hpp"
#include "utilsJson.hpp"
#include "draw_train.hpp"
#include "draw_rail_droite.hpp"
#include "draw_rail_courbe.hpp"
#include "draw_dino.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glbasimac/glbi_texture.hpp"

/// Camera parameters
float angle_theta{45.0}; // Angle between x axis and viewpoint
float angle_phy{30.0};	 // Angle between z axis and viewpoint
float dist_zoom{30.0};	 // Distance between origin and viewpoint

GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
// GLBI_Convex_2D_Shape ground{3};

StandardMesh *ground = NULL;
GLBI_Convex_2D_Shape ground_debug{3};
GLBI_Convex_2D_Shape RailInt;
GLBI_Convex_2D_Shape Rail1;
GLBI_Convex_2D_Shape Rail2;
GLBI_Convex_2D_Shape carre;
GLBI_Convex_2D_Shape triangle;

GLBI_Convex_2D_Shape courbeAvant1{3};
GLBI_Convex_2D_Shape courbeArriere1{3};
GLBI_Convex_2D_Shape courbeAvant2{3};
GLBI_Convex_2D_Shape courbeArriere2{3};

IndexedMesh *sphere = NULL;
IndexedMesh *balast = NULL;
IndexedMesh *rail = NULL;
IndexedMesh *cylindre = NULL;
StandardMesh *cone = NULL;
StandardMesh *rectangle = NULL;
IndexedMesh *cercle = NULL;
IndexedMesh *cube = NULL;

GLBI_Texture myTexture;

const float axe_x{10.0f};
const float axe_y{10.0f};
const float sx{0.75};
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
	myEngine.switchToPhongShading();
	myEngine.setLightIntensity(Vector3D(1000,1000,1000));
	myEngine.setLightPosition(Vector4D(0,-10,30,1));
	std::vector<float> points{0.0, 0.0, 0.0};
	somePoints.initSet(points, 1.0, 1.0, 1.0);

	std::vector<float> baseCarre{-100.0, -100.0, 0.0,
								 100.0, -100.0, 0.0,
								 100.0, 100.0, 0.0,
								 -100.0, 100.0, 0.0};
	myEngine.setNormalForConvex2DShape(Vector3D(0,0,1));
	ground.initShape(baseCarre);
	ground.changeNature(GL_TRIANGLE_FAN);
	myEngine.setNormalForConvex2DShape(Vector3D(0,0,1));



	// debug
	std::vector<float> carreDebug{
		0.0, 10.0, 0.11,
		10.0, 10.0, 0.11,
		10.0, 0.0, 0.11,
		0.0, 0.0, 0.11};

	ground_debug.initShape(carreDebug);
	ground_debug.changeNature(GL_TRIANGLE_FAN);
	myEngine.setNormalForConvex2DShape(Vector3D(0,0,1));


	balast = basicCylinder(1.0f, 1.0f);
	balast->createVAO();

	cylindre = basicCylinder(1.0f, 1.0f);
	cylindre->createVAO();

	rail = basicCube(1.0f);
	rail->createVAO();

	sphere = basicSphere(1.0f);
	sphere->createVAO();

	cone = basicCone(1.0f, 1.0f);
	cone->createVAO();

	rectangle = basicRect(1.0f, 1.0f);
	rectangle->createVAO();

	cercle = basicSphere(1.0f, 64, 64);
	cercle->createVAO();

	cube = basicCube(1.0f);
	cube->createVAO();


	// alors la je suis pas sur de l'initialisrtaion , dans le tp y'a ecrit c'est automatique mais ça crash chez moi donc je sais pas voila voila
	int width{512};
	int height{512};
	int channels{3};

	unsigned char *image_path =
		stbi_load("../assets/textures/green-grass.jpg", &width, &height, &channels, 0);

	if (image_path == nullptr)
	{
		std::cout << "erreur pas de texture" << std::endl;
		return;
	}

	myTexture.createTexture();
	myTexture.attachTexture();
	myTexture.setParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	myTexture.loadImage(width, height, channels, image_path);
	myTexture.detachTexture();
	stbi_image_free(image_path);

	// Rail courbé 2D
	std::vector<float> railIntPoints;
	int nbPoints = 100;
	float angleStep = (M_PI / 2.0f) / nbPoints;

	// courbes du haut et du bas pour rail 1
	std::vector<float> railIntPoints1;

	for (int i = 0; i <= nbPoints; i++)
	{
		float angle = i * angleStep;
		// intérieur de la bande
		railIntPoints1.push_back((POS_X_RAIL1 - sr / 2) * cos(angle));
		railIntPoints1.push_back((POS_X_RAIL1 - sr / 2) * sin(angle));


		// extérieur de la bande
		railIntPoints1.push_back((POS_X_RAIL1 + sr / 2) * cos(angle));
		railIntPoints1.push_back((POS_X_RAIL1 + sr / 2) * sin(angle));

	}
	Rail1.initShape(railIntPoints1);
	Rail1.changeNature(GL_TRIANGLE_STRIP);
	myEngine.setNormalForConvex2DShape(Vector3D(0,0,1));


	// courbes du haut et du bas pour rail 2
	std::vector<float> railIntPoints2;

	for (int i = 0; i <= nbPoints; i++)
	{
		float angle = i * angleStep;
		// intérieur de la bande
		railIntPoints2.push_back((POS_X_RAIL2 - sr / 2) * cos(angle));
		railIntPoints2.push_back((POS_X_RAIL2 - sr / 2) * sin(angle));


		// extérieur de la bande
		railIntPoints2.push_back((POS_X_RAIL2 + sr / 2) * cos(angle));
		railIntPoints2.push_back((POS_X_RAIL2 + sr / 2) * sin(angle));

	}
	Rail2.initShape(railIntPoints2);
	Rail2.changeNature(GL_TRIANGLE_STRIP);
	myEngine.setNormalForConvex2DShape(Vector3D(0,0,1));


	// courbes des côtés

	// avant 1
	std::vector<float> CourbeAvantPoints1;
	for (int i = 0; i <= nbPoints; i++)
	{
		float angle = i * angleStep;
		// dessus de la bande
		CourbeAvantPoints1.push_back((POS_X_RAIL1 - sr / 2) * cos(angle));
		CourbeAvantPoints1.push_back((POS_X_RAIL1 - sr / 2) * sin(angle));
		CourbeAvantPoints1.push_back(0);

		// dessous de la bande
		CourbeAvantPoints1.push_back((POS_X_RAIL1 - sr / 2) * cos(angle));
		CourbeAvantPoints1.push_back((POS_X_RAIL1 - sr / 2) * sin(angle));
		CourbeAvantPoints1.push_back(sr);
	}
	myEngine.setNormalForConvex2DShape(Vector3D(1,0,0));
	courbeAvant1.initShape(CourbeAvantPoints1);
	courbeAvant1.changeNature(GL_TRIANGLE_STRIP);

	// avant 2
	std::vector<float> CourbeAvantPoints2;
	for (int i = 0; i <= nbPoints; i++)
	{
		float angle = i * angleStep;
		// dessus de la bande
		CourbeAvantPoints2.push_back((POS_X_RAIL2 - sr / 2) * cos(angle));
		CourbeAvantPoints2.push_back((POS_X_RAIL2 - sr / 2) * sin(angle));
		CourbeAvantPoints2.push_back(0);

		// dessous de la bande
		CourbeAvantPoints2.push_back((POS_X_RAIL2 - sr / 2) * cos(angle));
		CourbeAvantPoints2.push_back((POS_X_RAIL2 - sr / 2) * sin(angle));
		CourbeAvantPoints2.push_back(sr);
	}
	courbeAvant2.initShape(CourbeAvantPoints2);
	courbeAvant2.changeNature(GL_TRIANGLE_STRIP);

	// arrière 1
	std::vector<float> CourbeArrierePoints1;
	for (int i = 0; i <= nbPoints; i++)
	{
		float angle = i * angleStep;
		// dessus de la bande
		CourbeArrierePoints1.push_back((POS_X_RAIL1 + sr / 2) * cos(angle));

		CourbeArrierePoints1.push_back((POS_X_RAIL1 + sr / 2) * sin(angle));
		CourbeArrierePoints1.push_back(0);

		// dessous de la bande
		CourbeArrierePoints1.push_back((POS_X_RAIL1 + sr / 2) * cos(angle));
		CourbeArrierePoints1.push_back((POS_X_RAIL1 + sr / 2) * sin(angle));
		CourbeArrierePoints1.push_back(sr);
	}
	courbeArriere1.initShape(CourbeArrierePoints1);
	courbeArriere1.changeNature(GL_TRIANGLE_STRIP);

	// arrière 1
	std::vector<float> CourbeArrierePoints2;
	for (int i = 0; i <= nbPoints; i++)
	{
		float angle = i * angleStep;
		// dessus de la bande
		CourbeArrierePoints2.push_back((POS_X_RAIL2 + sr / 2) * cos(angle));
		CourbeArrierePoints2.push_back((POS_X_RAIL2 + sr / 2) * sin(angle));
		CourbeArrierePoints2.push_back(0);

		// dessous de la bande
		CourbeArrierePoints2.push_back((POS_X_RAIL2 + sr / 2) * cos(angle));
		CourbeArrierePoints2.push_back((POS_X_RAIL2 + sr / 2) * sin(angle));
		CourbeArrierePoints2.push_back(sr);
	}
	courbeArriere2.initShape(CourbeArrierePoints2);
	courbeArriere2.changeNature(GL_TRIANGLE_STRIP);

	// carré

	std::vector<float> carre_points{1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f};

	carre.initShape(carre_points);
	carre.changeNature(GL_TRIANGLE_FAN);

	// triangle

	std::vector<float> triangle_points{0.0f, 0.0f, 1.0f, 0.0f, 0.5f, 0.5f};

	triangle.initShape(triangle_points);
	triangle.changeNature(GL_TRIANGLE_FAN);
}

void ground_position()
{
	myEngine.activateTexturing(true);
	myTexture.attachTexture();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D {0.0f, 0.0f, sr});
	myEngine.setFlatColor(0.749, 0.788, 0.82);
	myEngine.updateMvMatrix();
	Rail1.drawShape();
	Rail2.drawShape();

	// Dessus
	
	myEngine.mvMatrixStack.addTranslation(Vector3D{0.0f, 0.0f, sr});
	myEngine.updateMvMatrix();
	Rail1.drawShape();
	Rail2.drawShape();
	myEngine.mvMatrixStack.popMatrix();

	// carré 1 x
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, POS_X_RAIL1 - sr / 2.0f, rr));
	myEngine.mvMatrixStack.addRotation(-M_PI / 2.0f, y_axe);
	myEngine.mvMatrixStack.addHomothety(Vector3D(sr, sr, 1.0f));
	myEngine.updateMvMatrix();
	carre.drawShape();
	myEngine.mvMatrixStack.popMatrix();

	// carré 2 x
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, POS_X_RAIL2 - sr / 2.0f, rr));
	myEngine.mvMatrixStack.addRotation(-M_PI / 2.0f, y_axe);
	myEngine.mvMatrixStack.addHomothety(Vector3D(sr, sr, 1.0f));
	myEngine.updateMvMatrix();
	carre.drawShape();
	myEngine.mvMatrixStack.popMatrix();

	// carré 1 y
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(POS_X_RAIL1 - sr / 2.0f, 0.0f, 2 * rr));
	myEngine.mvMatrixStack.addRotation(-M_PI / 2.0f, x_axe);
	myEngine.mvMatrixStack.addHomothety(Vector3D(sr, sr, 1.0f));
	myEngine.updateMvMatrix();
	carre.drawShape();
	myEngine.mvMatrixStack.popMatrix();

	// carré 2 y
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(POS_X_RAIL2 - sr / 2.0f, 0.0f, 2 * rr));
	myEngine.mvMatrixStack.addRotation(-M_PI / 2.0f, x_axe);
	myEngine.mvMatrixStack.addHomothety(Vector3D(sr, sr, 1.0f));
	myEngine.updateMvMatrix();
	carre.drawShape();
	myEngine.mvMatrixStack.popMatrix();

	// milieu
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0,0,sr));
	myEngine.updateMvMatrix();
	courbeAvant1.drawShape();
	courbeArriere1.drawShape();
	courbeAvant2.drawShape();
	courbeArriere2.drawShape();
	myEngine.mvMatrixStack.popMatrix();
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



//void drawScene()
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
	// grid_pts.drawSet();

	somePoints.drawSet();

	myEngine.setFlatColor(0.435, 0.812, 0.592);

	ground_position();

	myEngine.setFlatColor(1, 0.984, 0);
	ground_debug.drawShape();
	myEngine.setFlatColor(0.2, 1.0, 0.8);

	// drawRailFer();
	// drawBalast();
	// drawRailDroite();
	//drawRailCourbe();
	drawRailFerCourbe();
	//rail_type_detect(config);
	//drawGare();
	//drawArbre();
	// drawBalast();
	// drawRailDroite();
	// drawRailDroite_position(0, 1);

	//  moteur();
	rail_type_detect(config);
	drawGare_position(config.origin);
	drawTrain();
	draw_dino();



	
	drawArbre();
}
