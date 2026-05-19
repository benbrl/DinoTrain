#include "utilsJson.hpp"

void from_json(const nlohmann::json &json, Position &position)
{
    json.at(0).get_to(position.x);
    json.at(1).get_to(position.y);
}

inline void to_json(nlohmann::json &json, const Position &position)
{
    json = nlohmann::json{position.x, position.y};
}

void from_json(const nlohmann::json &json, GridConfig &g)
{
    json.at("size_grid").get_to(g.size_grid);
    json.at("origin").get_to(g.origin);
    json.at("path").get_to(g.path);
}

void to_json(nlohmann::json &json, const GridConfig &g)
{
    json = nlohmann::json{
        {"size_grid", g.size_grid},
        {"origin", g.origin},
        {"path", g.path}};
}

GridConfig read_json()
{

    std::ifstream data("../data/data_new.json");

    if (!data)
    {
        std::cout << "Impossible d'ouvrir le fichier" << std::endl;
    }

    nlohmann::json json;
    data >> json;

    std::cout << "-------------- données non mondifié --------------" << std::endl;
    std::cout << json.dump(2) << std::endl;

    std::cout << "-------------- données parsé --------------" << std::endl;

    GridConfig config = json.get<GridConfig>();

    std::cout << "grid size : " << config.size_grid << std::endl;

    std::cout << "la valeur de l'origine : "
              << config.origin.x << ", "
              << config.origin.y << std::endl;

    for (auto const &valeur : config.path)
    {
        std::cout << valeur.x << ", " << valeur.y << std::endl;
    }

    return config;
}

void rail_type_detect(GridConfig config)
{
    std::cout << "-------------- debug config --------------" << std::endl;
    // debug

    std::vector<Position> rails = config.path;
    // for (auto const &valeur : rails)
    // {
    //     std::cout << valeur.x << ", " << valeur.y << std::endl;
    // }

    if ((rails[1].x == rails.back().x && rails[1].y != rails.back().y) || (rails[1].y == rails.back().y && rails[1].x != rails.back().x))
    {

        drawRailDroite_position(rails[1].x, rails[1].y);

        std::cout
            << "la rail " << 1 << " est droite " << std::endl;
    }
    else
    {
        // drawRailCourbe(rails[1].x, rails[1].y);
        std::cout << "la rail " << 1 << " est courbe" << std::endl;
    }

    for (size_t i = 0; i < rails.size(); i++)
    {

        if ((rails[i].x == rails[i + 2].x && rails[i].y != rails[i + 2].y) || (rails[i].y == rails[i + 2].y && rails[i].x != rails[i + 2].x))
        {

            drawRailDroite_position(rails[i + 1].x, rails[i + 1].y);

            std::cout << "la rail " << i + 1 << " est droite " << std::endl;
        }
        else
        {
            // drawRailCourbe(rails[i + 1].x, rails[i + 1].y);
            std::cout << "la rail " << i + 1 << " est courbe" << std::endl;
        }

        // a finir car la ça sort du si c'est la fin du tableau prendre le premeir element
    }
}