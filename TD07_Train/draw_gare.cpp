#include "draw_scene.hpp"
#include "utilsJson.hpp"
 
extern IndexedMesh *rail; 
//extern GLBI_Convex_2D_Shape carre; 
extern GLBI_Convex_2D_Shape triangle; 
extern StandardMesh *rectangle;

void drawToit(float dim_gare, float angle){

	float angle_toit = M_PI/2 - angle;
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0,0,dim_gare));
	myEngine.mvMatrixStack.addHomothety(Vector3D(dim_gare,(dim_gare/2.0f)/cos(angle),dim_gare));
	myEngine.mvMatrixStack.addRotation(-angle_toit, Vector3D(1,0,0));
	
	myEngine.updateMvMatrix();
	myEngine.setFlatColor(0, 0, 0.5);
	rectangle->draw();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, dim_gare, dim_gare));
	myEngine.mvMatrixStack.addHomothety(Vector3D(dim_gare, (dim_gare/2.0f)/cos(angle), dim_gare));
	myEngine.mvMatrixStack.addRotation( angle_toit, Vector3D(1,0,0));
	myEngine.updateMvMatrix();
	myEngine.setFlatColor(0, 0, 1);
	rectangle->draw();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(dim_gare, 0, dim_gare));
	myEngine.mvMatrixStack.addHomothety(Vector3D(dim_gare, dim_gare, dim_gare));
	myEngine.mvMatrixStack.addRotation( M_PI/2.0f, Vector3D(1,0,0));
	myEngine.mvMatrixStack.addRotation( M_PI/2.0f, Vector3D(0,1,0));
	myEngine.updateMvMatrix();
	triangle.drawShape();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0, dim_gare));
	myEngine.mvMatrixStack.addHomothety(Vector3D(dim_gare, dim_gare, dim_gare));
	myEngine.mvMatrixStack.addRotation( M_PI/2.0f, Vector3D(1,0,0));
	myEngine.mvMatrixStack.addRotation( M_PI/2.0f, Vector3D(0,1,0));
	myEngine.updateMvMatrix();
	triangle.drawShape();
	myEngine.mvMatrixStack.popMatrix();



}



void drawGare(){
	//murs
	float angle = M_PI/6.0f;
	
	float dim_gare = 10.0f;
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(dim_gare/2.0f, dim_gare/2.0f,dim_gare/2.0f));
	myEngine.mvMatrixStack.addHomothety(Vector3D(dim_gare, dim_gare, dim_gare));
	myEngine.updateMvMatrix();
	myEngine.setFlatColor(0.549, 0.353, 0.235);
	rail->draw();
	myEngine.mvMatrixStack.popMatrix();

	//toit
	drawToit(dim_gare, angle);
	
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation( M_PI/2.0f, Vector3D(0,0,1));
	float d = dim_gare/3.0f;
	myEngine.mvMatrixStack.addTranslation(Vector3D(0,-dim_gare, d));
	//myEngine.mvMatrixStack.addHomothety(Vector3D(1, 1, dim_gare));
	float dim{};

void drawGare_position(Position position)
{

	myEngine.mvMatrixStack.popMatrix();
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(position.x * 10, position.y * 10, 0));

	myEngine.updateMvMatrix();
	drawGare();
	myEngine.mvMatrixStack.popMatrix();
}
