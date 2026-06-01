#include "draw_rail_courbe.hpp"

extern const float sr;
extern const float rr;
extern const int POS_X_RAIL1;
extern Vector3D z_axe;
extern Vector3D y_axe;
extern Vector3D x_axe;

void drawRailCourbe()
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addRotation(-M_PI / 2, z_axe);

    // Les 3 balast
    myEngine.mvMatrixStack.pushMatrix();
    float angle = M_PI / 6;
    myEngine.mvMatrixStack.addRotation(M_PI / 12, z_axe);

    for (int i = 0; i < 3; ++i)
    {
        myEngine.mvMatrixStack.pushMatrix();
        myEngine.mvMatrixStack.addRotation(angle * i, z_axe);
        Vector3D trans2{0.0f, 2.0f, 0.0f};
        myEngine.mvMatrixStack.addTranslation(trans2);
        drawBalast();

        myEngine.mvMatrixStack.popMatrix();
    }
    myEngine.mvMatrixStack.popMatrix();
    myEngine.mvMatrixStack.popMatrix();

    // rail courbé int
    myEngine.mvMatrixStack.pushMatrix();
    drawRailFerCourbe();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void drawRailCourbe_position(int x, int y)
{
    // std::cout << "---------------- position rails ---------------" << std::endl;

    // std::cout << x << std::endl;
    // std::cout << y << std::endl;

    myEngine.mvMatrixStack.pushMatrix();

    myEngine.mvMatrixStack.addTranslation(Vector3D(x * 10, y * 10, 0));
    myEngine.updateMvMatrix();
    drawRailCourbe();

    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void drawRailFerCourbe()
{
    // Dessous
    myEngine.mvMatrixStack.pushMatrix();
    // myEngine.mvMatrixStack.addRotation(M_PI / 2.0f, z_axe);
    Vector3D trans3{0.0f, 0.0f, sr};
    myEngine.mvMatrixStack.addTranslation(trans3);
    myEngine.setFlatColor(0.749, 0.788, 0.82);
    myEngine.updateMvMatrix();
    Rail1.drawShape();
    Rail2.drawShape();

    // Dessus
    Vector3D trans4{0.0f, 0.0f, sr};
    myEngine.mvMatrixStack.addTranslation(trans4);
    myEngine.updateMvMatrix();
    Rail1.drawShape();
    Rail2.drawShape();
    myEngine.mvMatrixStack.popMatrix();

    // carré 1 x
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, POS_X_RAIL1 - sr / 2.0f, rr));
    myEngine.mvMatrixStack.addRotation(-M_PI / 2.0f, y_axe);
    myEngine.mvMatrixStack.addHomothety(Vector3D(sr, sr, 1.0f));
    myEngine.updateMvMatrix();
    carre.drawShape();
    myEngine.mvMatrixStack.popMatrix();

    // carré 2 x
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, POS_X_RAIL2 - sr / 2.0f, rr));
    myEngine.mvMatrixStack.addRotation(-M_PI / 2.0f, y_axe);
    myEngine.mvMatrixStack.addHomothety(Vector3D(sr, sr, 1.0f));
    myEngine.updateMvMatrix();
    carre.drawShape();
    myEngine.mvMatrixStack.popMatrix();

    // carré 1 y
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(POS_X_RAIL1 - sr / 2.0f, 0.0f, 2 * rr));
    myEngine.mvMatrixStack.addRotation(-M_PI / 2.0f, x_axe);
    myEngine.mvMatrixStack.addHomothety(Vector3D(sr, sr, 1.0f));
    myEngine.updateMvMatrix();
    carre.drawShape();
    myEngine.mvMatrixStack.popMatrix();

    // carré 2 y
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(POS_X_RAIL2 - sr / 2.0f, 0.0f, 2 * rr));
    myEngine.mvMatrixStack.addRotation(-M_PI / 2.0f, x_axe);
    myEngine.mvMatrixStack.addHomothety(Vector3D(sr, sr, 1.0f));
    myEngine.updateMvMatrix();
    carre.drawShape();
    myEngine.mvMatrixStack.popMatrix();

    // milieu
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0, sr));
    myEngine.updateMvMatrix();
    courbeAvant1.drawShape();
    courbeArriere1.drawShape();
    courbeAvant2.drawShape();
    courbeArriere2.drawShape();
    myEngine.mvMatrixStack.popMatrix();

    myEngine.mvMatrixStack.popMatrix();
}