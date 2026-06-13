#include "draw_rail_droite.hpp"

extern const float axe_y;
extern const float sx;
extern const float sr;
extern const float rr;
extern const int POS_X_RAIL1;
extern const int POS_X_RAIL2;
extern const float rayon_rail_balast;

void drawBalast()
{

	myEngine.mvMatrixStack.pushMatrix(),
		myEngine.mvMatrixStack.addHomothety(Vector3D(rayon_rail_balast, axe_y - 4, rayon_rail_balast));
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0, rayon_rail_balast * 2 + rr));
	myEngine.updateMvMatrix();
	myEngine.setFlatColor(0.549, 0.353, 0.235);
	balast->draw();

	myEngine.mvMatrixStack.popMatrix();
}

void drawRailFer()
{

	myEngine.mvMatrixStack.pushMatrix(),
		myEngine.mvMatrixStack.addHomothety(Vector3D(sr, axe_y, sr));

	myEngine.updateMvMatrix();
	myEngine.setFlatColor(0.749, 0.788, 0.82);
	rail->draw();

	myEngine.mvMatrixStack.popMatrix();
}

void drawRailDroite()
{

	// premier

	for (int i = 0; i < 5; ++i)
	{
		myEngine.mvMatrixStack.pushMatrix();

		myEngine.mvMatrixStack.addTranslation(Vector3D(sx + i * (2.0f * sx + rr), 2.0f, 0));
		myEngine.updateMvMatrix();
		drawBalast();

		myEngine.mvMatrixStack.popMatrix();
		myEngine.updateMvMatrix();
	}

	// rail fer droite
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation(deg2rad(90), Vector3D(0.0, 0.0, 1.0));
	// myEngine.mvMatrixStack.addTranslation(Vector3D(POS_X_RAIL1, -axe_y / 2 + sx * 2, rr));
	myEngine.mvMatrixStack.addTranslation(Vector3D(POS_X_RAIL1, -axe_y / 2, rr + sr / 2));
	myEngine.updateMvMatrix();
	drawRailFer();
	myEngine.mvMatrixStack.popMatrix();
	myEngine.updateMvMatrix();

	// rail fer gauche

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation(deg2rad(90), Vector3D(0.0, 0.0, 1.0));
	myEngine.mvMatrixStack.addTranslation(Vector3D(POS_X_RAIL2, -axe_y / 2, rr + sr / 2));
	myEngine.updateMvMatrix();
	drawRailFer();
	myEngine.mvMatrixStack.popMatrix();
	myEngine.updateMvMatrix();
}

void drawRailDroite_position(int x, int y, float rotation)
{
	myEngine.mvMatrixStack.pushMatrix();

	myEngine.mvMatrixStack.addTranslation(Vector3D(x * 10, y * 10, 0));
	myEngine.mvMatrixStack.addTranslation(Vector3D(5, 5, 0));

	if (rotation != 0)
	{
		myEngine.mvMatrixStack.addRotation(deg2rad(rotation), Vector3D(0, 0, 1));
	}

	myEngine.mvMatrixStack.addTranslation(Vector3D(-5, -5, 0));

	myEngine.updateMvMatrix();
	drawRailDroite();

	myEngine.mvMatrixStack.popMatrix();
	myEngine.updateMvMatrix();
}