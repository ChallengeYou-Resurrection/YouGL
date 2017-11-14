#ifndef CYWEBPARSER_H
#define CYWEBPARSER_H

#include <string>
#include <SFML/Network.hpp>

#include "CYLevel.h"

namespace CYWebParser {
    CYLevel* loadFileFromWebsite(int gameNumber);
    CYLevel* loadFileFromComputer(std::string filePath);
}

CYLevel* loadFile(std::string& levelCode);

#endif // CYWEBPARSER_H
