#include "draw_scene.hpp"
#include "utilsJson.hpp"
#include "draw_train.hpp"
#include "draw_rail_droite.hpp"
#include "draw_rail_courbe.hpp"
#include "draw_dino.hpp"

/// Camera parameters
float angle_theta{45.0}; // Angle between x axis and viewpoint
float angle_phy{30.0};	 // Angle between z axis and viewpoint
float dist_zoom{30.0};	 // Distance between origin and viewpoint

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

	std::vector<float> gridPoints;
	std::vector<float> gridColor;
	for (int i = 0; i <= 10; ++i)
	{
		// Parallèles à l'axe x
		gridPoints.push_back(-10 * 10 / 2.0f);
		gridPoints.push_back(-10 * 10 / 2.0f +
							 i * 10);
		gridPoints.push_back(0.1f);
		gridPoints.push_back(10 * 10 / 2.0f);
		gridPoints.push_back(-10 * 10 / 2.0f +
							 i * 10);
		gridPoints.push_back(0.1f);

		// Parallèles à l'axe y
		gridPoints.push_back(-10 * 10 / 2.0f +
							 i * 10);
		gridPoints.push_back(-10 * 10 / 2.0f);
		gridPoints.push_back(0.1f);
		gridPoints.push_back(-10 * 10 / 2.0f +
							 i * 10);
		gridPoints.push_back(10 * 10 / 2.0f);
		gridPoints.push_back(0.1f);
		for (unsigned int j = 0; j < 12; ++j)
		{
			gridColor.push_back(0.0f);
		}
	}
	grid_pts.initSet(gridPoints, gridColor);
	grid_pts.changeNature(GL_LINES);

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

void drawScene(GridConfig config)
{
	glPointSize(10.0);
	grid_pts.drawSet();

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
