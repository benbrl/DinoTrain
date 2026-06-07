#pragma once

#include "glbasimac/glbi_engine.hpp"
#include "glbasimac/glbi_set_of_points.hpp"
#include "glbasimac/glbi_convex_2D_shape.hpp"
#include "tools/basic_mesh.hpp"
#include "utilsJson.hpp"

void drawArbre();
void draw_position_arbre(int x, int y, int taille_arbre);
void draw_random_position_arbre(GridConfig config, int nb_arbres);