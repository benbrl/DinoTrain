#include "draw_dino.hpp"
#include "GLFW/glfw3.h"


void jambe()
{
    float rayon_jambe{0.2f};
    float taille_jambe{0.85f};

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(deg2rad(90), x_axe);
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

    // pied 1
    myEngine.mvMatrixStack.pushMatrix();

    myEngine.mvMatrixStack.addHomothety(Vector3D(0.5, 1.5, 0.5));
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.1, 0, 0));
    myEngine.updateMvMatrix();
    triangle.drawShape();
    myEngine.mvMatrixStack.popMatrix();

    // pied 2
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.5, 1.5, 0.5));
    myEngine.mvMatrixStack.addTranslation(Vector3D(-1.1, 0, 0));
    myEngine.updateMvMatrix();
    triangle.drawShape();
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

    // aile 1

    if (flagAnim)
    {
        nb_ms_elapsed = glfwGetTime() * 1000.0 - nb_ms_save;
    }
    float time = nb_ms_elapsed / 500.0f;
    float angle_mouv_main = sin(time) * 10.0f;

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.5, 0, -0.5));
    myEngine.mvMatrixStack.addRotation(deg2rad(angle_mouv_main), Vector3D(0, 1, 0));
    myEngine.mvMatrixStack.addHomothety(Vector3D(3, 3, 1.5));
    myEngine.mvMatrixStack.addRotation(deg2rad(-90), Vector3D(1, 0, 0));
    myEngine.mvMatrixStack.addRotation(deg2rad(-90), Vector3D(0, 0, 1));
    myEngine.updateMvMatrix();
    triangle.drawShape();
    myEngine.mvMatrixStack.popMatrix();

    // aile 2
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(-0.5, 0, -0.5));
    myEngine.mvMatrixStack.addHomothety(Vector3D(3, 3, 1.5));
    myEngine.mvMatrixStack.addRotation(deg2rad(-90), x_axe);
    myEngine.mvMatrixStack.addRotation(deg2rad(-90), z_axe);
    myEngine.mvMatrixStack.addRotation(deg2rad(180), z_axe);
    myEngine.mvMatrixStack.addTranslation(-x_axe);
    myEngine.updateMvMatrix();
    triangle.drawShape();
    myEngine.mvMatrixStack.popMatrix();
}

void draw_tete()
{

    // tete
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(deg2rad(-20), x_axe);
    myEngine.mvMatrixStack.addHomothety(Vector3D(1, 3, 1));
    myEngine.setFlatColor(0.357, 0.494, 0.235);
    myEngine.updateMvMatrix();
    cone->draw();
    myEngine.mvMatrixStack.popMatrix();

    // fin de la tete
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.setFlatColor(0.357, 0.494, 0.235);
    myEngine.updateMvMatrix();
    cercle->draw();
    myEngine.mvMatrixStack.popMatrix();

    // petit queue mais sur la tete
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(deg2rad(130), Vector3D(1.0, 0.0, 0.0));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.3, 1.5, 0.5));
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0.5, 0));
    myEngine.setFlatColor(0.357, 0.494, 0.235);
    myEngine.updateMvMatrix();
    cone->draw();
    myEngine.mvMatrixStack.popMatrix();

    // yeux 1
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.3, 0.3, 0.3));
    myEngine.mvMatrixStack.addTranslation(Vector3D(1, 4, 0));
    myEngine.setFlatColor(1, 1, 1);
    myEngine.updateMvMatrix();
    cercle->draw();
    myEngine.mvMatrixStack.popMatrix();

    // pupille 1
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.15, 0.15, 0.15));
    myEngine.mvMatrixStack.addTranslation(Vector3D(2.5, 9, 1.5));
    myEngine.setFlatColor(0.4, 0.7, 1.0);
    myEngine.updateMvMatrix();
    cercle->draw();
    myEngine.mvMatrixStack.popMatrix();

    // yeux 2

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.3, 0.3, 0.3));
    myEngine.mvMatrixStack.addTranslation(Vector3D(-1, 4, 0));
    myEngine.setFlatColor(1, 1, 1);
    myEngine.updateMvMatrix();
    cercle->draw();
    myEngine.mvMatrixStack.popMatrix();

    // pupille 2
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.15, 0.15, 0.15));
    myEngine.mvMatrixStack.addTranslation(Vector3D(-2.5, 9, 1.5));
    myEngine.setFlatColor(0.4, 0.7, 1.0);
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

    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0, 4.2));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.6, 0.6, 0.6));
    draw_tete();
    myEngine.mvMatrixStack.popMatrix();

    // petit queue
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(deg2rad(160), Vector3D(1.0, 0.0, 0.0));
    myEngine.mvMatrixStack.addHomothety(Vector3D(0.3, 1.5, 0.5));
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0.5, -3));
    myEngine.setFlatColor(0.357, 0.494, 0.235);
    myEngine.updateMvMatrix();
    cone->draw();
    myEngine.mvMatrixStack.popMatrix();
}

void draw_dino_position(GridConfig config)
{

    int x = config.dinosaure.position.x;
    int y = config.dinosaure.position.y;
    int rotation = config.dinosaure.rotation;
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.pushMatrix();

    myEngine.mvMatrixStack.addTranslation(Vector3D(x * 10, y * 10, 0));
    myEngine.mvMatrixStack.addRotation(deg2rad(rotation), z_axe);
    myEngine.updateMvMatrix();
    draw_dino();
    myEngine.mvMatrixStack.popMatrix();
}