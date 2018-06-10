#pragma once

#include <iostream>
#include <string>

#include <json.hpp>
#include "CYLevel.h"

namespace CYJsonParser {
	CYLevel loadFileFromDisk(const std::string& filePath);
}

CYLevel loadJsonFile(const std::string& levelCode);

