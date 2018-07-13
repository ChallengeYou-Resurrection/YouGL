#pragma once

#include <optional>
#include <string>
#include <unordered_map>

#include "../CYObjects/CYMiscObjects.h"

namespace OldFormat
{
    std::optional<std::string> loadFromWebsite(int gameNumber);
	std::optional<std::string> loadFromLocalhost(int gameNumber);
    std::unordered_map<std::string, std::string> getObjectTable(const std::string& levelCode);

    LevelHeader extractHeader(std::string& levelData);
    std::vector<Wall> extractWalls(std::string& wallData);
    std::vector<Platform> extractPlatforms(std::string& platformData);

    void massConvertFilesBinaryFormat();
}