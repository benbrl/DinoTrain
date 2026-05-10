#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#define _USE_MATH_DEFINES
#include <cmath>


#include <tools/globals.hpp>
#include <tools/gl_tools.hpp>
#include <tools/matrix4d.hpp>
#include <tools/matrix_stack.hpp>
#include <tools/shaders.hpp>
#include <tools/basic_mesh.hpp>

#include <iostream>

using namespace STP3D;

/* Variables gloables pour le dessin */

/*=============================================================================*/
/* VARIABLES (GLOBALES) POUR LE DESSIN (OPENGL)								   */
/*=============================================================================*/
// Parametres de l'application et d'OpenGL
extern GLuint idShader[3];
extern int initGLDone;
extern bool flagFilaire;
extern bool flagAnim;
extern float ratio;
extern unsigned int nb_ms_elapsed;
extern unsigned int nb_ms_save;
extern unsigned int idTexSkybox;

// Parametres de la camera
extern double rayon;
extern double angle_phy;
extern double angle_theta;

// Parametres de définition du monde et des transformations
extern double xmin,ymin,xmax,ymax; // Taille du "monde" en x et y
extern Matrix4D projMatrix;
extern Matrix4D viewMatrix;
extern MatrixStack modelviewStack;
extern StandardMesh* repere;
extern StandardMesh* ground;
extern IndexedMesh* a_basic_wolf;
extern IndexedMesh* sphere;
extern IndexedMesh* cyl;
extern StandardMesh* cone;

// Conversion degré en radians
inline float deg2rad(float deg) {
	return deg*3.1415926f/180.0f;
}

/***************************************************************************/
/*   FONCTIONS UTILITAIRES                                                 */
/***************************************************************************/
// Update the projection (to take into account ratio)
void resetProjMatrix();

// Send the geometric transformation to OpenGL
void updateMvMatrix(int ids = 0);

// Set a constant (and flat) color to future drawed object
void setFlatColor(float r,float g,float b);

// Create Skybox
void createSkyBox();

// Draw Skybox
void drawSky();

// Take a snapshot of the application
void makeSnapshot(std::string filename,int w,int h);

/***************************************************************************/
/*   FONCTION PRINCIPALE DE DESSIN (GL & INITIALISATION)                   */
/***************************************************************************/
void initGL();
void drawGround();
void drawWolf();
void drawWolves(int nb_wolfs);
void drawGoodWolf();
void drawGoodWolves(int nb_wolfs);
void drawAnimal();
void drawScene();
