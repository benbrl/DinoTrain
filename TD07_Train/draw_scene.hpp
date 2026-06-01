#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"
#include "utilsJson.hpp"

using namespace glbasimac;

/* Camera parameters and functions */
static const float Z_NEAR{0.1f};
static const float Z_FAR{500.f};
extern float angle_theta; // Angle between x axis and viewpoint
extern float angle_phy;   // Angle between z axis and viewpoint
extern float dist_zoom;   // Distance between origin and viewpoint

/* OpenGL Engine */
extern GLBI_Engine myEngine;

extern const float axe_y;
extern const float sx;
extern const float sr;
extern const float rr;
extern const int POS_X_RAIL1;
extern const int POS_X_RAIL2;
extern const float rayon_rail_balast;
extern GLBI_Convex_2D_Shape RailInt;
extern GLBI_Convex_2D_Shape carre;
extern IndexedMesh *balast;
extern IndexedMesh *rail;
extern IndexedMesh *sphere;
extern IndexedMesh *cercle;
extern IndexedMesh *cube;
extern IndexedMesh *cylindre;
extern StandardMesh *cone;

extern Vector3D z_axe;
extern Vector3D y_axe;
extern Vector3D x_axe;

void initScene();

void drawScene(GridConfig config);

void drawBalast();

void drawRailFer();

void drawRailDroite();

void drawGare();

void drawArbre();
