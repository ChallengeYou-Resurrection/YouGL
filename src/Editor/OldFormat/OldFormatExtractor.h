#pragma once

#include "OldFormatUtil.h"
#include "../CYObjects/CYWall.h"
#include "../CYObjects/CYPlat.h"

#include <regex>
#include <iostream>

namespace RegexExtractor
{
	const Property::Colour WHITE = { 255, 255, 255 };

	Property::Colour stringToColour(const std::string& colourString);
	Property::Position extractVector(const std::smatch& match, int firstIndex);
	Property::Material extractMaterial(const std::smatch& match, int firstIndex);
	u8 extractIntAsByte(const std::smatch& match, int firstIndex);
}