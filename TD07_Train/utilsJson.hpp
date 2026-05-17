#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "json.hpp"

struct Position
{
    int x{0};
    int y{0};
};

void to_json(nlohmann::json &json, const Position &position);

struct GridConfig
{
    int size_grid{0};
    Position origin{};
    std::vector<Position> path{};
};

void from_json(const nlohmann::json &json, GridConfig &g);
void to_json(nlohmann::json &json, const GridConfig &g);

GridConfig read_json();

void rail_type_detect(GridConfig config);