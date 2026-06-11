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
}

void drawRailCourbe_position(int x, int y, float rotation)
{
    // std::cout << "---------------- position rails ---------------" << std::endl;
    // std::cout << x << std::endl;
    // std::cout << y << std::endl;
    myEngine.mvMatrixStack.pushMatrix();

    myEngine.mvMatrixStack.addTranslation(Vector3D(x * 10, y * 10, 0));
    myEngine.mvMatrixStack.addTranslation(Vector3D(5, 5, 0));

    if (rotation != 0)
    {
        myEngine.mvMatrixStack.addRotation(deg2rad(rotation), Vector3D(0, 0, 1));
    }

    myEngine.mvMatrixStack.addTranslation(Vector3D(-5, -5, 0));

    myEngine.updateMvMatrix();
    drawRailCourbe();
    myEngine.mvMatrixStack.popMatrix();
    myEngine.updateMvMatrix();
}

void drawRailFerCourbe()
{
    // Dessous
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D{0.0f, 0.0f, sr});
    myEngine.setFlatColor(0.749, 0.788, 0.82);
    myEngine.setNormalForConvex2DShape(-z_axe);
    myEngine.updateMvMatrix();
    Rail1.drawShape();
    Rail2.drawShape();

    // Dessus
    myEngine.mvMatrixStack.addTranslation(Vector3D{0.0f, 0.0f, sr});
    myEngine.setNormalForConvex2DShape(z_axe);
    myEngine.updateMvMatrix();
    Rail1.drawShape();
    Rail2.drawShape();
    myEngine.mvMatrixStack.popMatrix();

    // carré 1 x
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(0.0f, POS_X_RAIL1 - sr / 2.0f, rr));
    myEngine.mvMatrixStack.addRotation(-M_PI / 2.0f, y_axe);
    myEngine.mvMatrixStack.addHomothety(Vector3D(sr, sr, 1.0f));
    myEngine.setNormalForConvex2DShape(x_axe);
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
    myEngine.setNormalForConvex2DShape(-y_axe);
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
    myEngine.setNormalForConvex2DShape(Vector3D{-cos(1.0f),-sin(1.0f),0.0f});
    myEngine.updateMvMatrix();
    courbeAvant1.drawShape();
    courbeAvant2.drawShape();
    myEngine.setNormalForConvex2DShape(Vector3D{cos(1.0f), sin(1.0f),0.0f});
    myEngine.updateMvMatrix();
    courbeArriere1.drawShape();
    courbeArriere2.drawShape();
    myEngine.mvMatrixStack.popMatrix();

    myEngine.mvMatrixStack.popMatrix();
}