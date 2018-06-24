#pragma once
#include "glm/vec3.hpp"

constexpr float WORLD_SIZE = 30.0f;
constexpr float WORLD_HEIGHT = 12.f;

const float TEXTURE_SIZE = 5. / 4.f;

namespace Coordinate
{
	static glm::vec3 WorldToLevel(const glm::vec3& coord)
	{
		return glm::vec3(coord.x * WORLD_SIZE, coord.y * WORLD_SIZE,
			coord.z * WORLD_SIZE);
	}
}