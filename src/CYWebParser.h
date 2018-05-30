#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <SFML/Network.hpp>
#include <optional>

#include "CYLevel.h"

namespace CYWebParser {
    std::optional<CYLevel> loadFileFromWebsite(int gameNumber);
    //CYLevel* loadFileFromComputer(std::string filePath);
}

std::optional<CYLevel> loadFile(const std::string& levelCode);
std::map<std::string, std::string> classifiedLevelCode(const std::string& levelCode);

