/***************************************************************************/
/*                      PROGRAMME PRINCIPAL                                */
/* Auteur : V. Biri                                                        */
/* Application : Wolf => Affichage d'un loup                               */
/***************************************************************************/
#include "rendering.hpp"

using namespace STP3D;

/***************************************************************************/
/*                       FONCTIONS DE GESTION CLAVIER                      */
/***************************************************************************/
void keyPressZoomIn() {
	if (rayon>10.0) rayon *= 0.9;
}

void keyPressZoomOut() {
	if (rayon < 800.0) rayon *= 1.1;
}

void keyPressPanLeft() {
	angle_theta -= 1.0;
}

void keyPressPanRight() {
	angle_theta += 1.0;
}

void keyPressPanUp() {
	if (angle_phy < 85) angle_phy += 1.0;
}

void keyPressPanDown() {
	if (angle_phy > -85) angle_phy -= 1.0;
}

/* Error handling function */
void onError(int error, const char* description)
{
	std::cerr<<"GLFW Error ("<<error<<"): "<<description<<std::endl;
}

void onWindowResized(GLFWwindow* /* window */, int width, int height)
{
	// adjust the viewport when the window is resized
	glViewport(0, 0, width, height);
	ratio = (float)width/(float)height;
	resetProjMatrix();
}

void onKey(GLFWwindow* window, int key, int /* scancode */, int action, int /* mods */)
{
	// Ce flag permet de savoir si la touche est pressee (car elle aussi peut etre "relachee" ou "repetee")
	int is_pressed = (action == GLFW_PRESS); 
	switch(key) {
		case GLFW_KEY_A :
		case GLFW_KEY_ESCAPE :
			if (is_pressed) glfwSetWindowShouldClose(window,GLFW_TRUE);
			break;
		case GLFW_KEY_F :
			if (is_pressed) {
				flagFilaire = !flagFilaire;
				std::cout <<"Mode filaire : "<<((flagFilaire)?"ON":"OFF")<<std::endl;
			}
			break;
		case GLFW_KEY_I :
			if (is_pressed) {
				int width, height;
				glfwGetWindowSize(window, &width, &height);
				makeSnapshot("snapshot.png",width,height);
			}
			break;
		case GLFW_KEY_SPACE :
			if (is_pressed) {
				flagAnim = !flagAnim;
				std::cout <<"Animation : "<<((flagAnim)?"ON":"OFF")<<std::endl;
				if (flagAnim) nb_ms_save = glfwGetTime()*1000.0;
			}
			break;
		case GLFW_KEY_P :
			keyPressZoomIn();
			break;
		case GLFW_KEY_SEMICOLON :
			keyPressZoomOut();
			break;
		case GLFW_KEY_UP :
			keyPressPanUp();
			break;
		case GLFW_KEY_DOWN :
			keyPressPanDown();
			break;
		case GLFW_KEY_LEFT :
			keyPressPanLeft();
			break;
		case GLFW_KEY_RIGHT :
			keyPressPanRight();
			break;
		default: 
			std::cout<<"Touche non gérée "<<key<<std::endl;
	}
}


int main(int /* argc */, char** /* argv */)
{
	/* GLFW initialisation */
	GLFWwindow* window;
	if (!glfwInit()) return -1;

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

    /* A RAJOUTER */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(800,800,"Open GL", NULL, NULL);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	gladLoadGL();

	glfwSetWindowSizeCallback(window,onWindowResized);
	glfwSetKeyCallback(window, onKey);

	onWindowResized(window,800,800);

	// Initialisation OpenGL
	initGL(); // cf fichier rendering.cpp

	// *****************  IHM  ************************* //

	nb_ms_save = 0;

	while (!glfwWindowShouldClose(window))
    {
        // On efface la fenetre
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Dessin (cf fichier rendering.cpp)
		drawScene();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
		// Actualisation du temps
		if (flagAnim) {
			nb_ms_elapsed = glfwGetTime()*1000.0 - nb_ms_save;
		}
    }

	glfwTerminate();

	return 0;
}
