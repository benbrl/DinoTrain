#include "draw_dino.hpp"

void jambe()
{
    float rayon_jambe{0.2f};
    float taille_jambe{0.85f};

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(deg2rad(90), Vector3D(1.0, 0.0, 0.0));
    myEngine.mvMatrixStack.addHomothety(Vector3D(rayon_jambe, taille_jambe, rayon_jambe));

    myEngine.setFlatColor(0.357, 0.494, 0.235);
    myEngine.updateMvMatrix();

    cylindre->draw();
    myEngine.mvMatrixStack.popMatrix();
}

void draw_foot()
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.3, 0, 0));
    myEngine.updateMvMatrix();
    jambe();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-0.3, 0, 0));
    myEngine.updateMvMatrix();
    jambe();
    myEngine.mvMatrixStack.popMatrix();
}

void draw_corps()
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.8, 0.4, 1.4));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.357, 0.494, 0.235);
    myEngine.updateMvMatrix();

    cercle->draw();
    myEngine.mvMatrixStack.popMatrix();
}

void draw_dino()
{
    draw_foot();
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0, 2));
    draw_corps();
    myEngine.mvMatrixStack.popMatrix();

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0, 3));
    jambe();
    myEngine.mvMatrixStack.popMatrix();
}