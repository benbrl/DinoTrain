#include "draw_scene.hpp"
#include "utilsJson.hpp"

extern IndexedMesh *balast;
extern IndexedMesh *sphere;
extern StandardMesh *cone;

void drawArbre(){


    int taille_arbre = 4;

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addHomothety(Vector3D(1, 1, taille_arbre));
    myEngine.mvMatrixStack.addRotation(M_PI/2, Vector3D(1,0,0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.549, 0.353, 0.235);
    balast->draw();
    myEngine.mvMatrixStack.addHomothety(Vector3D(taille_arbre,1,taille_arbre));
    myEngine.mvMatrixStack.addTranslation(Vector3D(0,1,0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0, 0.05, 0);
    cone->draw();
    for(int i=1; i<=taille_arbre; i++)
    {
        myEngine.mvMatrixStack.addHomothety(Vector3D(0.75,1,0.75));
        myEngine.mvMatrixStack.addTranslation(Vector3D(0,0.5,0));
        myEngine.updateMvMatrix();
        myEngine.setFlatColor(0, 0.5*(i+1)/10, 0);
        cone->draw();
    }
   
    myEngine.mvMatrixStack.popMatrix();
    

    // myEngine.mvMatrixStack.pushMatrix();
    // myEngine.mvMatrixStack.addTranslation(Vector3D(1,1,tronc_dim));
    // myEngine.mvMatrixStack.addRotation(M_PI/2, Vector3D(1,0,0));
    // myEngine.updateMvMatrix();
    // myEngine.setFlatColor(0, 1, 0);
    // cone->draw();
    // myEngine.mvMatrixStack.popMatrix();
}