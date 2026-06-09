#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "draw_scene.hpp"
#include "tools/shaders.hpp"
#include <iostream>
#include "utilsJson.hpp"

using namespace glbasimac;
using namespace STP3D;
using json = nlohmann::json;

/* Window properties */
static const unsigned int WINDOW_WIDTH = 800;
static const unsigned int WINDOW_HEIGHT = 800;
static const char WINDOW_TITLE[] = "Dino Train";
static float aspectRatio = 1.0f;

/* Minimal time wanted between two images */
static const double FRAMERATE_IN_SECONDS = 1. / 30.;

/* Error handling function */
void onError(int error, const char *description)
{
	std::cout << "GLFW Error (" << error << ") : " << description << std::endl;
}

void onWindowResized(GLFWwindow * /*window*/, int width, int height)
{
	aspectRatio = width / (float)height;

	glViewport(0, 0, width, height);
	std::cerr << "Setting 3D projection" << std::endl;

	myEngine.set3DProjection(90.0, aspectRatio, Z_NEAR, Z_FAR);
}

Vector3D pos_camera   = Vector3D(0, 0,  10);
Vector3D front_vector = Vector3D(0.0f, 1.0f, 0.0f);
Vector3D up_vector    = Vector3D(0.0f, 0.0f,  1.0f);
float lastFrame = 0.0f;
// float currentFrame = glfwGetTime();
// float deltaTime    = currentFrame - lastFrame;
// lastFrame          = currentFrame;
float deltaTime    = 1.0f;
float a{0};
float b = M_PI/12.0f;
float cameraSpeed = 2.5f * deltaTime;
Vector3D right = (front_vector ^ up_vector);



void onKey(GLFWwindow *window, int key, int /*scancode*/, int action, int /*mods*/)
{
	right.normalize();
	int is_pressed = (action == GLFW_PRESS);
	switch (key)
	{
	case GLFW_KEY_A:
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	case GLFW_KEY_L:
		if (is_pressed)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case GLFW_KEY_P:
		if (is_pressed)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;

	case GLFW_KEY_UP:
		pos_camera += front_vector * cameraSpeed;
		break;
	case GLFW_KEY_DOWN:
		pos_camera -= front_vector * cameraSpeed;
		break;
	case GLFW_KEY_LEFT:
		pos_camera -= right * cameraSpeed;
		break;
	case GLFW_KEY_RIGHT:
		pos_camera += right * cameraSpeed;
		break;
	case GLFW_KEY_D:
    a += b;
    front_vector = Vector3D(cos(a), -sin(a), 0);
    right = (front_vector ^ up_vector);
    right.normalize();
    break;
	case GLFW_KEY_S:
    a -= b;
    front_vector = Vector3D(cos(a), -sin(a), 0);
    right = (front_vector ^ up_vector);
    right.normalize();
    break;
	case GLFW_KEY_R:
		dist_zoom -= 0.9;
		break;
	case GLFW_KEY_T:
		dist_zoom += 0.9;
		break;
	case GLFW_KEY_B:
		myEngine.switchToPhongShading();
		break;
	case GLFW_KEY_F:
		myEngine.switchToFlatShading();
		break;

	default:
		std::cerr << "Touche non gérée " << key << std::endl;
	}
}

void onMouseButton(GLFWwindow *window, int button, int action, int /*mods*/)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		std::cout << "Pressed in " << xpos << " " << ypos << std::endl;
	}
}

int main(int /*argc*/, char ** /*argv*/)
{

	std::string ascii = R"(
 ____  _               _____          _       
|  _ \(_)_ __   ___   |_   _| __ __ _(_)_ __  
| | | | | '_ \ / _ \    | || '__/ _` | | '_ \ 
| |_| | | | | | (_) |   | || | | (_| | | | | |
|____/|_|_| |_|\___/    |_||_|  \__,_|_|_| |_|

  par Benoît Baraille et Jade Riesen
    )";

	std::cout << ascii << std::endl;

	GridConfig config;
	config = read_json();

	/* GLFW initialisation */
	GLFWwindow *
		window;
	if (!glfwInit())
		return -1;

	/* Try to uncomment this for MAC OS if it did not work */
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	/* Callback to a function if an error is rised by GLFW */
	glfwSetErrorCallback(onError);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
	if (!window)
	{
		// If no context created : exit !
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	std::cout << "Loading GL extension" << std::endl;
	// Intialize glad (loads the OpenGL functions)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return -1;
	}

	glfwSetWindowSizeCallback(window, onWindowResized);
	glfwSetKeyCallback(window, onKey);
	glfwSetMouseButtonCallback(window, onMouseButton);

	myEngine.mode2D = false; // Set engine to 3D mode

	std::cout << "Engine init" << std::endl;

	myEngine.initGL();

	onWindowResized(window, WINDOW_WIDTH, WINDOW_HEIGHT);
	CHECK_GL;

	initScene();

	double elapsedTime{0.0};


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Get time (in second) at loop beginning */
		double startTime = glfwGetTime();

		/* Render begins here */
		glClearColor(0.f, 0.0f, 0.2f, 0.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		 	
myEngine.mvMatrixStack.loadIdentity();
Matrix4D viewMatrix = Matrix4D::lookAt(pos_camera, pos_camera + front_vector, up_vector);
myEngine.setViewMatrix(viewMatrix);
myEngine.updateMvMatrix();

drawScene(config);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Elapsed time computation from loop begining */
		elapsedTime = glfwGetTime() - startTime;
		/* If to few time is spend vs our wanted FPS, we wait */
		while (elapsedTime < FRAMERATE_IN_SECONDS)
		{
			glfwWaitEventsTimeout(FRAMERATE_IN_SECONDS - elapsedTime);
			elapsedTime = glfwGetTime() - startTime;
		}
	}

	glfwTerminate();
	return 0;
}
