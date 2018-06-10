#pragma once

#include <iostream>
#include <string>
#include <regex>
#include <SFML/Network.hpp>
#include <optional>

#include "CYLevel.h"

namespace CYWebParser {
    CYLevel loadFileFromWebsite(int gameNumber);
	CYLevel loadFileFromDisk(const std::string& filePath);
}

CYLevel loadFile(const std::string& levelCode);
std::map<std::string, std::string> classifiedLevelCode(const std::string& levelCode);

