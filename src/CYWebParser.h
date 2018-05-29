#ifndef CYWEBPARSER_H
#define CYWEBPARSER_H

#include <iostream>
#include <string>
#include <regex>
#include <SFML/Network.hpp>

#include "CYLevel.h"

namespace CYWebParser {
    CYLevel* loadFileFromWebsite(int gameNumber);
    CYLevel* loadFileFromComputer(std::string filePath);
}

CYLevel* loadFile(const std::string& levelCode);
std::map<std::string, std::string> classifiedLevelCode(const std::string& levelCode);

#endif // CYWEBPARSER_H
