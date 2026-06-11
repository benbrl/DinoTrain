#include "draw_scene.hpp"
#include "utilsJson.hpp"
#include <vector>
#include <iostream>

extern IndexedMesh *balast;
extern IndexedMesh *sphere;
extern StandardMesh *cone;

struct Arbre
{
    int x;
    int y;
    int taille;
};

std::vector<Arbre> liste_arbres;

void drawArbre(int taille_arbre)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addHomothety(Vector3D(1, 1, taille_arbre));
    myEngine.mvMatrixStack.addRotation(M_PI / 2, Vector3D(1, 0, 0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0.549, 0.353, 0.235);
    balast->draw();
    myEngine.mvMatrixStack.addHomothety(Vector3D(taille_arbre, 1, taille_arbre));
    myEngine.mvMatrixStack.addTranslation(Vector3D(0, 1, 0));
    myEngine.updateMvMatrix();
    myEngine.setFlatColor(0, 0.05, 0);
    cone->draw();
    for (int i = 1; i <= taille_arbre; i++)
    {
        myEngine.mvMatrixStack.addHomothety(Vector3D(0.75, 1, 0.75));
        myEngine.mvMatrixStack.addTranslation(Vector3D(0, 0.5, 0));
        myEngine.updateMvMatrix();
        myEngine.setFlatColor(0, 0.5 * (i + 1) / 10, 0);
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

void liste_position_arbre(GridConfig config, int nb_arbres)
{
    std::vector<Position> rails = config.path;

    liste_arbres.clear();
    int arbres_places = 0;

    while (arbres_places < nb_arbres)
    {
        int arbre_position_x = rand() % 10 - 5;
        int arbre_position_y = rand() % 10 - 5;

        // minimum de taille 2
        int taille = rand() % 5 + 2;

        bool isRail = false;
        for (const Position &rail : rails)
        {
            if (rail.x == arbre_position_x && rail.y == arbre_position_y)
            {
                isRail = true;
                break;
            }
        }

        if (!isRail)
        {
            liste_arbres.push_back({arbre_position_x, arbre_position_y, taille});
            arbres_places++;
        }
    }

    // debug
    // for (auto const &arbre : liste_arbres)
    // {
    //     std::cout << arbre.x << ", " << arbre.y << " taille  :" << arbre.taille << std::endl;
    // }
}

void draw_position_arbre(int arbre_position_x, int arbre_position_y, int taille_arbre)
{
    myEngine.mvMatrixStack.pushMatrix();
    myEngine.mvMatrixStack.addTranslation(Vector3D(arbre_position_x * 10, arbre_position_y * 10, 0));
    myEngine.updateMvMatrix();
    drawArbre(taille_arbre);
    myEngine.mvMatrixStack.popMatrix();
}

void draw_random_position_arbre(GridConfig config)
{

    int nb_arbres = config.arbres;
    // genere une fois la liste pour pas de nouveau random 60 fois/s
    if (liste_arbres.empty())
    {
        liste_position_arbre(config, nb_arbres);
    }

    for (const Arbre &arbre_position : liste_arbres)
    {
        draw_position_arbre(arbre_position.x, arbre_position.y, arbre_position.taille);
    }
}