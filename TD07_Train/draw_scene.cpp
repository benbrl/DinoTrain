#include "draw_scene.hpp"

/// Camera parameters
float angle_theta{45.0}; // Angle between x axis and viewpoint
float angle_phy{30.0};	 // Angle between z axis and viewpoint
float dist_zoom{30.0};	 // Distance between origin and viewpoint

GLBI_Engine myEngine;
GLBI_Set_Of_Points somePoints(3);
GLBI_Convex_2D_Shape ground{3};

IndexedMesh *sphere = NULL;

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

	// Une sphere de rayon 10 (représentée par 16 bandes de 32 triangles)
	sphere = basicSphere(10.0f, 16, 16);
	sphere->createVAO();
}

void drawFrame()
{
	// TO DO
}

void drawBase()
{
	// TO DO
}

void drawArm()
{
	// TO DO
}

void drawPan()
{
	// TO DO
}

void drawScene()
{
	glPointSize(10.0);

	somePoints.drawSet();

	myEngine.setFlatColor(0.435, 0.812, 0.592);
	ground.drawShape();
	myEngine.setFlatColor(0.2, 1.0, 0.8);
	sphere->draw();
}
