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

void from_json(const nlohmann::json &json, Dinosaure &dinosaure)
{
    json.at(0).get_to(dinosaure.position.x);
    json.at(1).get_to(dinosaure.position.y);
    json.at(2).get_to(dinosaure.rotation);
}

void to_json(nlohmann::json &json, const Dinosaure &dinosaure)
{
    json = nlohmann::json{dinosaure.position.x, dinosaure.position.y, dinosaure.rotation};
}

void from_json(const nlohmann::json &json, GridConfig &g)
{
    json.at("size_grid").get_to(g.size_grid);
    json.at("origin").get_to(g.origin);
    json.at("arbres").get_to(g.arbres);
    json.at("dinosaure").get_to(g.dinosaure);
    json.at("path").get_to(g.path);
}

void to_json(nlohmann::json &json, const GridConfig &g)
{
    json = nlohmann::json{
        {"size_grid", g.size_grid},
        {"origin", g.origin},
        {"arbres", g.arbres},
        {"dinosaure", g.dinosaure},
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
    // std::cout << "-------------- debug config --------------" << std::endl;
    std::vector<Position> rails = config.path;
    // for (auto const &valeur : rails)
    // {
    //     std::cout << valeur.x << ", " << valeur.y << std::endl;
    // }

    if ((rails[1].x == rails.back().x && rails[1].y != rails.back().y) || (rails[1].y == rails.back().y && rails[1].x != rails.back().x))
    {
        float rotation = 0.0f;

        if (rails[1].x != rails.back().x)
        {
            rotation = 0.0f;
        }
        else
        {
            rotation = 90.0f;
        }

        drawRailDroite_position(rails[0].x, rails[0].y, rotation);
        // std::cout << "la rail " << 0 << " est droite " << std::endl;
    }
    else
    {
        float rotation = 0.0f;
        if (((rails[0].x - rails.back().x) == 1 && (rails[1].y - rails[0].y) == 1) || ((rails[0].y - rails.back().y) == -1 && (rails[1].x - rails[0].x) == -1))
        {
            rotation = 270.0f;
        }
        else if (((rails[0].y - rails.back().y) == 1 && (rails[1].x - rails[0].x) == -1) || ((rails[0].x - rails.back().x) == 1 && (rails[1].y - rails[0].y) == -1))
        {
            rotation = 0.0f;
        }
        else if (((rails[0].x - rails.back().x) == -1 && (rails[1].y - rails[0].y) == -1) || ((rails[0].y - rails.back().y) == 1 && (rails[1].x - rails[0].x) == 1))
        {
            rotation = 90.0f;
        }
        else if (((rails[0].y - rails.back().y) == -1 && (rails[1].x - rails[0].x) == 1) || ((rails[0].x - rails.back().x) == -1 && (rails[1].y - rails[0].y) == 1))
        {
            rotation = 180.0f;
        }
        drawRailCourbe_position(rails[0].x, rails[0].y, rotation);
    }

    for (size_t i = 0; i < rails.size() - 2; i++)
    {
        if ((rails[i].x == rails[i + 2].x && rails[i].y != rails[i + 2].y) || (rails[i].y == rails[i + 2].y && rails[i].x != rails[i + 2].x))
        {
            drawRailDroite_position(rails[i + 1].x, rails[i + 1].y, (rails[i].x != rails[i + 2].x) ? 0.0f : 90.0f);
            // std::cout << "la rail " << i + 1 << " est droite " << std::endl;
        }
        else
        {
            float rotation = 0.0f;
            if (((rails[i + 1].x - rails[i].x) == 1 && (rails[i + 2].y - rails[i + 1].y) == 1) || ((rails[i + 1].y - rails[i].y) == -1 && (rails[i + 2].x - rails[i + 1].x) == -1))
            {
                rotation = 270.0f;
            }
            else if (((rails[i + 1].y - rails[i].y) == 1 && (rails[i + 2].x - rails[i + 1].x) == -1) || ((rails[i + 1].x - rails[i].x) == 1 && (rails[i + 2].y - rails[i + 1].y) == -1))
            {
                rotation = 0.0f;
            }

            else if (((rails[i + 1].x - rails[i].x) == -1 && (rails[i + 2].y - rails[i + 1].y) == -1) || ((rails[i + 1].y - rails[i].y) == 1 && (rails[i + 2].x - rails[i + 1].x) == 1))
            {
                rotation = 90.0f;
            }
            else if (((rails[i + 1].y - rails[i].y) == -1 && (rails[i + 2].x - rails[i + 1].x) == 1) || ((rails[i + 1].x - rails[i].x) == -1 && (rails[i + 2].y - rails[i + 1].y) == 1))
            {
                rotation = 180.0f;
            }
            drawRailCourbe_position(rails[i + 1].x, rails[i + 1].y, rotation);
        }
    }

    if ((rails[rails.size() - 2].x == rails[0].x && rails[rails.size() - 2].y != rails[0].y) || (rails[rails.size() - 2].y == rails[0].y && rails[rails.size() - 2].x != rails[0].x))
    {

        float rotation = 0.0f;

        if (rails[rails.size() - 2].x != rails[0].x)
        {
            rotation = 0.0f;
        }
        else
        {
            rotation = 90.0f;
        }

        drawRailDroite_position(rails.back().x, rails.back().y, rotation);
        // std::cout << "la rail " << rails.size() - 1 << " est droite " << std::endl;
    }
    else
    {
        float rotation = 0.0f;
        if (((rails.back().x - rails[rails.size() - 2].x) == 1 && (rails[0].y - rails.back().y) == 1) || ((rails.back().y - rails[rails.size() - 2].y) == -1 && (rails[0].x - rails.back().x) == -1))
        {
            rotation = 270.0f;
        }
        else if (((rails.back().y - rails[rails.size() - 2].y) == 1 && (rails[0].x - rails.back().x) == -1) || ((rails.back().x - rails[rails.size() - 2].x) == 1 && (rails[0].y - rails.back().y) == -1))
        {
            rotation = 0.0f;
        }
        else if (((rails.back().x - rails[rails.size() - 2].x) == -1 && (rails[0].y - rails.back().y) == -1) || ((rails.back().y - rails[rails.size() - 2].y) == 1 && (rails[0].x - rails.back().x) == 1))
        {
            rotation = 90.0f;
        }
        else if (((rails.back().y - rails[rails.size() - 2].y) == -1 && (rails[0].x - rails.back().x) == 1) || ((rails.back().x - rails[rails.size() - 2].x) == -1 && (rails[0].y - rails.back().y) == 1))
        {
            rotation = 180.0f;
        }
        drawRailCourbe_position(rails.back().x, rails.back().y, rotation);
    }
}