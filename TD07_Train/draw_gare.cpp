#include "draw_scene.hpp"
#include "utilsJson.hpp"

extern IndexedMesh *rail;
// extern GLBI_Convex_2D_Shape carre;
extern GLBI_Convex_2D_Shape triangle;
extern StandardMesh *rectangle;

float taille_pilone = 1;
float hauteur_pilone = 5;
float largeur_auvent = 4.f;
float hauteur_auvent = 1.f;
float longeur_auvent = 10.f;
float angle = M_PI / 6.0f;

float hauteur_gare = 6.f;
float largeur_gare = 4;
float angle_toit = M_PI / 2 - angle;
float dim_gare = largeur_gare+largeur_auvent;
void drawEntree()
{
	

	// pylone 1
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, taille_pilone / 2.0f, hauteur_pilone / 2.0f));
	myEngine.mvMatrixStack.addHomothety(Vector3D(taille_pilone, taille_pilone, hauteur_pilone));
	myEngine.setFlatColor(0.643, 0.447, 0.318);
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();

	// pylone 2
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, 10 - taille_pilone + taille_pilone / 2.f, hauteur_pilone / 2.0f));
	myEngine.mvMatrixStack.addHomothety(Vector3D(taille_pilone, taille_pilone, hauteur_pilone));
	myEngine.setFlatColor(0.643, 0.447, 0.318);
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();

	// auvent
	
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(-hauteur_auvent - taille_pilone / 2, longeur_auvent / 2.0f, hauteur_pilone + hauteur_auvent / 2.f));
	myEngine.mvMatrixStack.addHomothety(Vector3D(largeur_auvent, longeur_auvent, hauteur_auvent));
	myEngine.setFlatColor(0.643, 0.447, 0.318);
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();

	// rotation pylone 1
	float hauteur_pilone_rotation = 3.7f;
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, taille_pilone + 1.0f, hauteur_pilone - 1.0f));
	myEngine.mvMatrixStack.addRotation(deg2rad(-45), Vector3D(1, 0, 0));
	myEngine.mvMatrixStack.addHomothety(Vector3D(taille_pilone, taille_pilone, hauteur_pilone_rotation));
	myEngine.setFlatColor(0.643, 0.447, 0.318);
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();

	// rotation pylone 2
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, 10 - taille_pilone - 1.0f, hauteur_pilone - 1.0f));
	myEngine.mvMatrixStack.addRotation(deg2rad(45), Vector3D(1, 0, 0));
	myEngine.mvMatrixStack.addHomothety(Vector3D(taille_pilone, taille_pilone, hauteur_pilone_rotation));
	myEngine.setFlatColor(0.643, 0.447, 0.318);
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();
}

void drawGare()
{
	

	// murs
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(largeur_gare / 2.0, longeur_auvent/ 2.f, hauteur_gare / 2.f));
	myEngine.mvMatrixStack.addHomothety(Vector3D(largeur_gare, longeur_auvent, hauteur_gare));
	myEngine.updateMvMatrix();
	myEngine.setFlatColor(0.549, 0.353, 0.235);
	rail->draw();
	myEngine.mvMatrixStack.popMatrix();

	// toit
		
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D{dim_gare,0, 0});
	myEngine.mvMatrixStack.addRotation(M_PI/2.0f, z_axe);
	myEngine.setFlatColor(0.1, 0.13, 0.15);
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0, hauteur_gare));
	myEngine.mvMatrixStack.addHomothety(Vector3D(longeur_auvent, (dim_gare / 2.0f) / cos(angle), dim_gare));
	myEngine.mvMatrixStack.addRotation(-angle_toit, Vector3D(1, 0, 0));
	myEngine.updateMvMatrix();
	rectangle->draw();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, dim_gare, hauteur_gare));
	myEngine.mvMatrixStack.addHomothety(Vector3D(longeur_auvent, (dim_gare / 2.0f) / cos(angle), dim_gare));
	myEngine.mvMatrixStack.addRotation(angle_toit, Vector3D(1, 0, 0));
	myEngine.updateMvMatrix();
	rectangle->draw();
	myEngine.mvMatrixStack.popMatrix();
	
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(longeur_auvent, 0, hauteur_gare));
	myEngine.mvMatrixStack.addHomothety(Vector3D(dim_gare, dim_gare, dim_gare));
	myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, Vector3D(1, 0, 0));
	myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, Vector3D(0, 1, 0));
	myEngine.updateMvMatrix();
	triangle.drawShape();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0, hauteur_gare));
	myEngine.mvMatrixStack.addHomothety(Vector3D(dim_gare, dim_gare, dim_gare));
	myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, Vector3D(1, 0, 0));
	myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, Vector3D(0, 1, 0));
	myEngine.updateMvMatrix();
	triangle.drawShape();
	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(7.5, 0, 0));
	myEngine.updateMvMatrix();
	drawEntree();
	myEngine.mvMatrixStack.popMatrix();

	

}

void drawGare_position(Position position)
{

	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(position.x * 10, position.y * 10, 0));

	myEngine.updateMvMatrix();
	drawGare();
	myEngine.mvMatrixStack.popMatrix();
}
