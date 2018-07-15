#pragma once

#include <optional>
#include <string>
#include <unordered_map>

#include "../CYObjects/CYMiscObjects.h"
#include "../CYObjects/CYGeneric.h"

namespace OldFormat
{
    std::optional<std::string> loadFromWebsite(int gameNumber);
	std::optional<std::string> loadFromLocalhost(int gameNumber);
    std::unordered_map<std::string, std::string> getObjectTable(const std::string& levelCode);

    LevelHeader extractHeader(std::string& levelData);
	std::vector<std::shared_ptr<CYGeneric>> extractGeometry(std::unordered_map<std::string, std::string>& table);

    void massConvertFilesBinaryFormat();
}