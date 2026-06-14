#include "draw_train.hpp"

float hauteur_cube{2};
float longeur_cube{4};
float largeur_cube{7};

double marge_sol{1.5};

float marge{0.5};

float taille_cylindre{1};

void rectangle()
{

	myEngine.mvMatrixStack.pushMatrix(),
		myEngine.updateMvMatrix();
	myEngine.setFlatColor(0.878, 0.329, 0.329);
	cube->draw();

	myEngine.mvMatrixStack.popMatrix();
}

void roue()
{

	myEngine.mvMatrixStack.pushMatrix(),
		myEngine.updateMvMatrix();
	myEngine.setFlatColor(1, 0.788, 0.302);
	cercle->draw();

	myEngine.mvMatrixStack.popMatrix();
}

void corps_roue()
{
	// corps du train
	myEngine.mvMatrixStack.pushMatrix();

	float marge_largeur = 5.0f;
	float marge_longeur = 5.0f;
	float marge_hauteur = hauteur_cube / 2 + marge_sol;
	float largeur_roue = 0.2f;
	float rayon_roue = 1.0f;
	float rayon_petite = 0.5f;
	float x_gauche = marge_largeur - longeur_cube / 2 - largeur_roue / 2;
	float x_droit = marge_largeur + longeur_cube / 2 + largeur_roue / 2;
	float y_arriere_1 = marge_longeur - largeur_cube / 2 + rayon_roue;
	float y_arriere_2 = y_arriere_1 + 2 * rayon_roue + marge;
	float y_avant = marge_longeur + largeur_cube / 2 - rayon_petite;
	float z_grosse = marge_hauteur - hauteur_cube / 2; // posées sur le sol
	float z_petite = z_grosse;
	float hauteur_roue_grande = rayon_roue / 2 + rayon_roue + rr;
	float hauteur_roue_petite = rayon_petite / 2 + rayon_petite + rr;

	myEngine.mvMatrixStack.addTranslation(Vector3D(marge_largeur, marge_longeur, marge_hauteur));
	myEngine.mvMatrixStack.addHomothety(Vector3D(longeur_cube, largeur_cube, hauteur_cube));
	myEngine.setFlatColor(0.878, 0.329, 0.329);
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();

	// roue arriere gauche premiere
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(x_gauche, y_arriere_1, hauteur_roue_grande));
	myEngine.mvMatrixStack.addRotation(deg2rad(90),z_axe);
	myEngine.mvMatrixStack.addHomothety(Vector3D(rayon_roue, largeur_roue, rayon_roue));
	myEngine.setFlatColor(1, 0.788, 0.302);
	myEngine.updateMvMatrix();
	cercle->draw();
	myEngine.mvMatrixStack.popMatrix();

	// roue arriere gauche deuxieme
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(x_gauche, y_arriere_2, hauteur_roue_grande));
	myEngine.mvMatrixStack.addRotation(deg2rad(90), Vector3D(0.0, 0.0, 1.0));
	myEngine.mvMatrixStack.addHomothety(Vector3D(rayon_roue, largeur_roue, rayon_roue));
	myEngine.setFlatColor(1, 0.788, 0.302);
	myEngine.updateMvMatrix();
	cercle->draw();
	myEngine.mvMatrixStack.popMatrix();

	// roue arriere droite premiere
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(x_droit, y_arriere_1, hauteur_roue_grande));
	myEngine.mvMatrixStack.addRotation(deg2rad(90), z_axe);
	myEngine.mvMatrixStack.addHomothety(Vector3D(rayon_roue, largeur_roue, rayon_roue));
	myEngine.setFlatColor(1, 0.788, 0.302);
	myEngine.updateMvMatrix();
	cercle->draw();
	myEngine.mvMatrixStack.popMatrix();

	// roue arriere droite deuxieme
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(x_droit, y_arriere_2, hauteur_roue_grande));
	myEngine.mvMatrixStack.addRotation(deg2rad(90), z_axe);
	myEngine.mvMatrixStack.addHomothety(Vector3D(rayon_roue, largeur_roue, rayon_roue));
	myEngine.setFlatColor(1, 0.788, 0.302);
	myEngine.updateMvMatrix();
	cercle->draw();
	myEngine.mvMatrixStack.popMatrix();

	// petite roue avant 1
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(x_gauche, y_avant - 1.3, z_petite));
	myEngine.mvMatrixStack.addRotation(deg2rad(90), z_axe);
	myEngine.mvMatrixStack.addHomothety(Vector3D(rayon_petite, largeur_roue, rayon_petite));
	myEngine.setFlatColor(1, 0.788, 0.302);
	myEngine.updateMvMatrix();
	cercle->draw();
	myEngine.mvMatrixStack.popMatrix();

	// petite roue avant 2
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(x_droit, y_avant - 1.3, z_petite));
	myEngine.mvMatrixStack.addRotation(deg2rad(90), z_axe);
	myEngine.mvMatrixStack.addHomothety(Vector3D(rayon_petite, largeur_roue, rayon_petite));
	myEngine.setFlatColor(1, 0.788, 0.302);
	myEngine.updateMvMatrix();
	cercle->draw();
	myEngine.mvMatrixStack.popMatrix();

	// petite roue avant 3
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(x_gauche, y_avant, z_petite));
	myEngine.mvMatrixStack.addRotation(deg2rad(90), z_axe);
	myEngine.mvMatrixStack.addHomothety(Vector3D(rayon_petite, largeur_roue, rayon_petite));
	myEngine.setFlatColor(1, 0.788, 0.302);
	myEngine.updateMvMatrix();
	cercle->draw();
	myEngine.mvMatrixStack.popMatrix();

	// petite roue avant 14
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(x_droit, y_avant, z_petite));
	myEngine.mvMatrixStack.addRotation(deg2rad(90), z_axe);
	myEngine.mvMatrixStack.addHomothety(Vector3D(rayon_petite, largeur_roue, rayon_petite));
	myEngine.setFlatColor(1, 0.788, 0.302);
	myEngine.updateMvMatrix();
	cercle->draw();
	myEngine.mvMatrixStack.popMatrix();
}

void moteur()
{

	float rayon_moteur{1.f};
	float taille_moteur{3.f};

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation(deg2rad(90), x_axe);
	myEngine.mvMatrixStack.addHomothety(Vector3D(rayon_moteur, taille_moteur, rayon_moteur));

	myEngine.setFlatColor(0.878, 0.329, 0.329);
	myEngine.updateMvMatrix();

	cylindre->draw();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation(deg2rad(90), x_axe);
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, taille_moteur / 2, 0));
	myEngine.mvMatrixStack.addHomothety(Vector3D(rayon_moteur * 1.5, taille_moteur / 4, rayon_moteur * 1.5));

	myEngine.setFlatColor(0.878, 0.329, 0.329);
	myEngine.updateMvMatrix();

	cylindre->draw();

	myEngine.mvMatrixStack.popMatrix();
}

void cercle_jaune()
{
	float rayon_cercle{.55f};
	float epaisseur_cercle{0.3f}; // très plat
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addHomothety(Vector3D(rayon_cercle, epaisseur_cercle, rayon_cercle));
	myEngine.updateMvMatrix();
	myEngine.setFlatColor(1, 0.788, 0.302);
	cylindre->draw();
	myEngine.mvMatrixStack.popMatrix();
}

void petales()
{
	float hauteur_petale = -2;

	float distance_centre = 0.5f;
	float angle = 20.f;

	// petale avant
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, hauteur_petale, distance_centre));
	myEngine.mvMatrixStack.addRotation(deg2rad(-angle), x_axe);
	cercle_jaune();
	myEngine.mvMatrixStack.popMatrix();

	// petale arriere
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, hauteur_petale, -distance_centre));
	myEngine.mvMatrixStack.addRotation(deg2rad(angle), x_axe);
	cercle_jaune();
	myEngine.mvMatrixStack.popMatrix();

	// petale droite
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(distance_centre, hauteur_petale, 0));
	myEngine.mvMatrixStack.addRotation(deg2rad(angle), z_axe);
	cercle_jaune();
	myEngine.mvMatrixStack.popMatrix();

	// petale gauche
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(-distance_centre, hauteur_petale, 0));
	myEngine.mvMatrixStack.addRotation(deg2rad(-angle), z_axe);
	cercle_jaune();
	myEngine.mvMatrixStack.popMatrix();
}

/// cheminé en mode tchou tchou
void cheminee()
{
	float rayon_cheminee{0.7f};
	float taille_cheminee{1.f};

	// cylindre vert
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation(deg2rad(90), x_axe);
	myEngine.mvMatrixStack.addHomothety(Vector3D(rayon_cheminee, taille_cheminee, rayon_cheminee));
	myEngine.setFlatColor(0.188, 0.427, 0.161);
	myEngine.updateMvMatrix();
	cylindre->draw();
	myEngine.mvMatrixStack.popMatrix();

	// cylindre jaune
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation(deg2rad(90), x_axe);
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, taille_cheminee, 0));
	myEngine.mvMatrixStack.addHomothety(Vector3D(rayon_cheminee, taille_cheminee, rayon_cheminee));
	myEngine.setFlatColor(1, 0.788, 0.302);
	myEngine.updateMvMatrix();
	cylindre->draw();
	myEngine.mvMatrixStack.popMatrix();

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addRotation(deg2rad(90), x_axe);
	myEngine.mvMatrixStack.addTranslation(Vector3D(0, taille_cheminee * 4, 0));
	myEngine.updateMvMatrix();
	petales();

	myEngine.mvMatrixStack.popMatrix();
}

void cabine()
{
	float marge_largeur = ((10 - longeur_cube) / 2) + longeur_cube / 2;
	float marge_longeur = ((10 - largeur_cube) / 2) + largeur_cube / 2;
	float marge_hauteur = hauteur_cube / 2 + marge_sol;

	// cylindre rouge

	float largeur_bloc = 0.5f;

	float hauteur_cabine = 2.f;

	float x_min = marge_largeur - longeur_cube / 2;
	float x_max = marge_largeur + longeur_cube / 2;
	float y_min = marge_longeur - largeur_cube / 2;
	float z_haut = marge_hauteur + hauteur_cube / 2 - hauteur_cabine / 2 + hauteur_cabine;

	// coin arriere gauche
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(x_min + largeur_bloc / 2, y_min + largeur_bloc / 2, z_haut));
	myEngine.mvMatrixStack.addHomothety(Vector3D(largeur_bloc, largeur_bloc, hauteur_cabine));

	myEngine.setFlatColor(0.188, 0.427, 0.161);
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();

	// coin arrierte droit
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(x_max - largeur_bloc / 2, y_min + largeur_bloc / 2, z_haut));
	myEngine.mvMatrixStack.addHomothety(Vector3D(largeur_bloc, largeur_bloc, hauteur_cabine));
	myEngine.setFlatColor(0.188, 0.427, 0.161);
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();

	// coin avant gauche
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(x_min + largeur_bloc / 2, 5, z_haut));
	myEngine.mvMatrixStack.addHomothety(Vector3D(largeur_bloc, largeur_bloc, hauteur_cabine));
	myEngine.setFlatColor(0.188, 0.427, 0.161);
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();

	// coin avant droit
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(x_max - largeur_bloc / 2, 5, z_haut));
	myEngine.mvMatrixStack.addHomothety(Vector3D(largeur_bloc, largeur_bloc, hauteur_cabine));

	myEngine.setFlatColor(0.188, 0.427, 0.161);
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();

	// le toit

	float hauteur_toit = 0.2f;
	float longueur_toit = largeur_cube - 3;
	float z_toit = marge_hauteur + hauteur_cube / 2 + hauteur_cabine + hauteur_toit / 2;
	float centre_x = (x_min + x_max) / 2;

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(centre_x, longueur_toit - largeur_bloc, z_toit));
	myEngine.mvMatrixStack.addHomothety(Vector3D(longeur_cube, longueur_toit, hauteur_toit));

	myEngine.setFlatColor(0.188, 0.427, 0.161);
	myEngine.updateMvMatrix();
	cube->draw();
	myEngine.mvMatrixStack.popMatrix();
}

void drawTrain()
{

	corps_roue();
	cabine();
	// cylindre moteur

	// cheminee
	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(5, 7, 3.5));
	myEngine.mvMatrixStack.addHomothety(Vector3D(0.7, 0.7, 0.7));
	cheminee();
	myEngine.updateMvMatrix();
	myEngine.mvMatrixStack.popMatrix();

	// moteur

	myEngine.mvMatrixStack.pushMatrix();
	myEngine.mvMatrixStack.addTranslation(Vector3D(5, 8, 3.5));
	myEngine.mvMatrixStack.addRotation(deg2rad(-90), x_axe);
	myEngine.mvMatrixStack.addHomothety(Vector3D(0.6, 0.6, 0.6));
	myEngine.updateMvMatrix();
	moteur();

	myEngine.mvMatrixStack.popMatrix();
}