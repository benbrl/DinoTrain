#include "rendering.hpp"

GLuint idShader[3];
int initGLDone = 0;
bool flagFilaire = false;
bool flagRunning = true;
bool flagAnim = false;
float ratio = 1.0f;
unsigned int nb_ms_elapsed = 0;
unsigned int nb_ms_save = 0;
unsigned int idTexSkybox = 0;

// Camera parameters
double rayon = 300.0;
double angle_phy = 15.0;
double angle_theta = 45.0;

// Parametres du monde et des transformations
double xmin = -400.0, ymin = -400.0, xmax = +400.0, ymax = +400.0;
Matrix4D projMatrix;
Matrix4D viewMatrix;
MatrixStack modelviewStack;
StandardMesh *repere = NULL;
StandardMesh *ground = NULL;
IndexedMesh *a_basic_wolf = NULL;
IndexedMesh *sphere = NULL;
IndexedMesh *cyl = NULL;
StandardMesh *cone = NULL;

/***************************************************************************/
/*   FONCTIONS PRINCIPALES DE DESSIN                                       */
/***************************************************************************/
void initGL()
{
	/**********************************************
	 * GL BUSINESS - NE PAS CHERCHER A COMPRENDRE
	 **********************************************/
	projMatrix = Matrix4D::perspective(45.0, ratio, 1.0f, 2000.0f);

	idShader[0] = ShaderManager::loadShader("../shaders/flat_shading.vert", "../shaders/flat_shading.frag", false);
	idShader[1] = ShaderManager::loadShader("../shaders/tex_shading.vert", "../shaders/tex_shading.frag", false);
	printf("Shader initialized !\n");

	glUseProgram(idShader[1]);
	glActiveTexture(GL_TEXTURE0);
	createSkyBox();

	glUseProgram(idShader[0]);

	/*******************************************
	 * CREATION DES OBJETS DE BASE (CANONIQUES)
	 *******************************************/
	repere = createRepere(100.0f);
	repere->createVAO(); // Creation de l'objet dans OpenGL

	ground = basicRect(xmax - xmin, ymax - ymin);
	ground->createVAO(); // Creation de l'objet dans OpenGL

	// Le "basic wolf" est, en fait, un simple cube de taille 20
	a_basic_wolf = basicCube(20.0f);
	a_basic_wolf->createVAO(); // Creation de l'objet dans OpenGL

	// Une sphere de rayon 10 (représentée par 16 bandes de 32 triangles)
	sphere = basicSphere(10.0f, 16, 16);
	sphere->createVAO(); // Creation de l'objet dans OpenGL

	// Un cylindre de hauteur 20 et de rayon 5
	cyl = basicCylinder(20.0, 5.);
	cyl->createVAO(); // Creation de l'objet dans OpenGL

	// Un cone de hauteur 20 et de rayon 5
	cone = basicCone(20.0, 5.);
	cone->createVAO(); // Creation de l'objet dans OpenGL

	CHECK_GL;

	initGLDone = 1;
	std::cout << "Initialisation is done !" << std::endl;
}

void drawGround()
{
	modelviewStack.pushMatrix();

	modelviewStack.addRotation(deg2rad(90), Vector3D(1.0, 0.0, 0.0));
	modelviewStack.addTranslation(Vector3D(-(xmax - xmin) / 2, 0.0, -(ymax - ymin) / 2));

	updateMvMatrix(0);
	setFlatColor(0.0, 0.4, 0.0);
	ground->draw();
	repere->draw();
	modelviewStack.popMatrix();
}

void drawBasicWolf()
{
	modelviewStack.pushMatrix();

	modelviewStack.addTranslation(Vector3D(0.0, 0.0, 10));
	modelviewStack.addHomothety(Vector3D(1.0, 2.0, 1.0));
	updateMvMatrix();
	setFlatColor(0.5, 0.5, 0.5);
	a_basic_wolf->draw();

	modelviewStack.popMatrix();
}
void drawWolves(int nb_wolfs)
{
	int rayon = 100;
	float base_angle = 360.0f / nb_wolfs;

	float rotation = (nb_ms_elapsed / 1000.0f);

	for (int i = 0; i < nb_wolfs; i++)
	{
		modelviewStack.pushMatrix();

		float angle_deg = base_angle * i + rotation * 50.0f;
		float angle_rad = angle_deg * (3.14f / 180.0f);

		float position_x = cos(angle_rad) * rayon;
		float position_y = sin(angle_rad) * rayon;

		modelviewStack.addTranslation(Vector3D(position_x, position_y, 0.0f));
		modelviewStack.addRotation(angle_rad, Vector3D(0, 0, 1));

		drawGoodWolf();

		modelviewStack.popMatrix();
	}
}

void drawGoodWolf()
{

	

	modelviewStack.pushMatrix();

	modelviewStack.addTranslation(Vector3D(0.0, 0.0, 20));
	modelviewStack.addHomothety(Vector3D(1.0, 2.0, 1.0));
	updateMvMatrix(0);
	setFlatColor(0.58, 0.294, 0);
	a_basic_wolf->draw();
	modelviewStack.popMatrix();

	modelviewStack.pushMatrix();
	modelviewStack.addTranslation(Vector3D(0.0, 20.0, 27.5));
	modelviewStack.addHomothety(Vector3D(1.3, 1.3, 1.3));
	updateMvMatrix(0);
	setFlatColor(1.0, 0.847, 0.702);
	sphere->draw();
	modelviewStack.popMatrix();

	modelviewStack.pushMatrix();
	modelviewStack.addRotation(deg2rad(90), Vector3D(1.0, 0.0, 0.0));
	modelviewStack.addTranslation(Vector3D(-10 + 1.25, 5, -20 + 1.25));
	modelviewStack.addHomothety(Vector3D(0.25, 0.25, 0.25));
	updateMvMatrix(0);
	setFlatColor(0.388, 0.2, 0.004);
	cyl->draw();
	modelviewStack.popMatrix();

	modelviewStack.pushMatrix();
	modelviewStack.addRotation(deg2rad(90), Vector3D(1.0, 0.0, 0.0));
	modelviewStack.addTranslation(Vector3D(10 - 1.25, 5, -20 + 1.25));
	modelviewStack.addHomothety(Vector3D(0.25, 0.25, 0.25));
	updateMvMatrix(0);
	setFlatColor(0.388, 0.2, 0.004);
	cyl->draw();
	modelviewStack.popMatrix();

	modelviewStack.pushMatrix();
	modelviewStack.addRotation(deg2rad(90), Vector3D(1.0, 0.0, 0.0));
	modelviewStack.addTranslation(Vector3D(-10 + 1.25, 5, 20 - 1.25));
	modelviewStack.addHomothety(Vector3D(0.25, 0.25, 0.25));
	updateMvMatrix(0);
	setFlatColor(0.388, 0.2, 0.004);
	cyl->draw();
	modelviewStack.popMatrix();

	modelviewStack.pushMatrix();
	modelviewStack.addRotation(deg2rad(90), Vector3D(1.0, 0.0, 0.0));
	modelviewStack.addTranslation(Vector3D(10 - 1.25, 5, 20 - 1.25));
	modelviewStack.addHomothety(Vector3D(0.25, 0.25, 0.25));
	updateMvMatrix(0);
	setFlatColor(0.388, 0.2, 0.004);
	cyl->draw();
	modelviewStack.popMatrix();

	// cone

	modelviewStack.pushMatrix();
	modelviewStack.addRotation(deg2rad(-90), Vector3D(1.0, 0.0, 0.0));
	modelviewStack.addTranslation(Vector3D(-10 + 1.25, -5, -20 + 1.25));
	modelviewStack.addHomothety(Vector3D(0.25, 0.25, 0.25));
	updateMvMatrix(0);
	setFlatColor(1.0, 0.847, 0.702);
	cone->draw();
	modelviewStack.popMatrix();

	modelviewStack.pushMatrix();
	modelviewStack.addRotation(deg2rad(-90), Vector3D(1.0, 0.0, 0.0));
	modelviewStack.addTranslation(Vector3D(10 - 1.25, -5, -20 + 1.25));
	modelviewStack.addHomothety(Vector3D(0.25, 0.25, 0.25));
	updateMvMatrix(0);
	setFlatColor(1.0, 0.847, 0.702);
	cone->draw();
	modelviewStack.popMatrix();

	modelviewStack.pushMatrix();
	modelviewStack.addRotation(deg2rad(-90), Vector3D(1.0, 0.0, 0.0));
	modelviewStack.addTranslation(Vector3D(-10 + 1.25, -5, 20 - 1.25));
	modelviewStack.addHomothety(Vector3D(0.25, 0.25, 0.25));
	updateMvMatrix(0);
	setFlatColor(1.0, 0.847, 0.702);
	cone->draw();
	modelviewStack.popMatrix();

	modelviewStack.pushMatrix();
	modelviewStack.addRotation(deg2rad(-90), Vector3D(1.0, 0.0, 0.0));
	modelviewStack.addTranslation(Vector3D(10 - 1.25, -5, 20 - 1.25));
	modelviewStack.addHomothety(Vector3D(0.25, 0.25, 0.25));
	updateMvMatrix(0);
	setFlatColor(1.0, 0.847, 0.702);
	cone->draw();
	modelviewStack.popMatrix();

	// museau

	modelviewStack.pushMatrix();

	modelviewStack.addTranslation(Vector3D(0.0, 30, 27.5));
	modelviewStack.addHomothety(Vector3D(1, 1, 0.5));
	updateMvMatrix(0);
	setFlatColor(0.69, 0.25, 0.098);
	cone->draw();
	modelviewStack.popMatrix();

	modelviewStack.pushMatrix();
	modelviewStack.addTranslation(Vector3D(0.0, 30, 27.5));
	modelviewStack.addHomothety(Vector3D(1, 1, 0.5));
	updateMvMatrix(0);
	setFlatColor(0.487214, 0.8091, 0.13423);
	cone->draw();
	modelviewStack.popMatrix();

	// queue
	// modelviewStack.pushMatrix();

	// modelviewStack.addTranslation(Vector3D(0.0, -17, 25));
	// modelviewStack.addRotation(deg2rad(225), Vector3D(1, 0, 0));
	// modelviewStack.addHomothety(Vector3D(1.2, 1.8, 0.25));
	// updateMvMatrix(0);
	// setFlatColor(0.9, 0.9, 0.9);
	// cone->draw();
	// modelviewStack.popMatrix();

	// queue

	float time = nb_ms_elapsed / 1000.0f;
	float angle_mouv_queue = 110 + sin(time * 4.0f) * 20.0f;

	modelviewStack.pushMatrix();

	modelviewStack.addTranslation(Vector3D(0.0, -18, 25));
	modelviewStack.addRotation(deg2rad(angle_mouv_queue), Vector3D(1, 0, 0));
	modelviewStack.addHomothety(Vector3D(1.2, 1.5, 0.25));
	updateMvMatrix(0);
	setFlatColor(0.69, 0.25, 0.098);
	cone->draw();
	modelviewStack.popMatrix();

	// oreille
	modelviewStack.pushMatrix();
	modelviewStack.addRotation(deg2rad(90.0f), Vector3D(1.0, 0.0, 0.0));
	modelviewStack.addTranslation(Vector3D(-5.0, 35.0, -25.0));
	modelviewStack.addHomothety(Vector3D(0.8, 0.8, 0.5));

	setFlatColor(0.69, 0.25, 0.098);
	updateMvMatrix(0);
	cone->draw();
	modelviewStack.popMatrix();

	modelviewStack.pushMatrix();
	modelviewStack.addRotation(deg2rad(90.0f), Vector3D(1.0, 0.0, 0.0));
	modelviewStack.addTranslation(Vector3D(5.0, 35.0, -25.0));
	modelviewStack.addHomothety(Vector3D(0.8, 0.8, 0.5));

	setFlatColor(0.69, 0.25, 0.098);
	updateMvMatrix(0);
	cone->draw();
	modelviewStack.popMatrix();
}

void drawAnimal()
{
}

void drawScene(void)
{
	/*****************************************
	 * GL BUSINESS - DO NOT TRY TO UNDERSTAND
	 *****************************************/
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	if (flagFilaire)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// CHECK_GL;
	glUseProgram(idShader[0]);
	glUniformMatrix4fv(glGetUniformLocation(idShader[0], "projectionMat"), 1, GL_FALSE, projMatrix);
	glUseProgram(idShader[1]);
	glUniformMatrix4fv(glGetUniformLocation(idShader[1], "projectionMat"), 1, GL_FALSE, projMatrix);
	glUseProgram(idShader[0]);

	/***************************************
	 * CAMERA SETTING
	 ***************************************/
	Vector3D pos_camera = Vector3D(rayon * cos(deg2rad(angle_theta)) * cos(deg2rad(angle_phy)),
								   rayon * sin(deg2rad(angle_theta)) * cos(deg2rad(angle_phy)),
								   rayon * sin(deg2rad(angle_phy)));
	Vector3D viewed_point = Vector3D(0.0, 0.0, 0.0);

	Vector3D up_vector = Vector3D(0.0, 0.0, 1.0); // DO NOT TOUCH IT
	viewMatrix = Matrix4D::lookAt(pos_camera, viewed_point, up_vector);
	// CHECK_GL;

	/***************************************
	 * DESSIN DE LA SCENE
	 ***************************************/
	modelviewStack.pushMatrix();
	modelviewStack.addTransformation(viewMatrix);
	updateMvMatrix(0);

	// DESSIN DE LA SKY BOX : NE PAS TOUCHER
	drawSky();

	// DESSIN DU REPERE DU MONDE
	repere->draw();

	// DESSIN DU SOL
	drawGround();

	// DESSIN DU LOUP
	// drawBasicWolf();

	drawWolves(6);

	modelviewStack.popMatrix();

	// Verification des erreurs OpenGL
	// CHECK_GL;
}
