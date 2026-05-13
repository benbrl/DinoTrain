#include "utilsJson.hpp"

struct Position
{
    int x{0};
    int y{0};
};

void from_json(const nlohmann::json &json, Position &position)
{
    json.at(0).get_to(position.x);
    json.at(1).get_to(position.y);
}

inline void to_json(nlohmann::json &json, const Position &position)
{
    json = nlohmann::json{position.x, position.y};
}

struct GridConfig
{
    int size_grid{0};
    Position origin{};
    std::vector<Position> path{};
};

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

void read_json()
{

    std::ifstream data("../data/data.json");

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
}