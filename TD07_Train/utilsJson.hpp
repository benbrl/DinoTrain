#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "json.hpp"


struct Position;

void to_json(nlohmann::json &json, const Position &position);

struct GridConfig;

void from_json(const nlohmann::json &json, GridConfig &g);
void to_json(nlohmann::json &json, const GridConfig &g);

void read_json();