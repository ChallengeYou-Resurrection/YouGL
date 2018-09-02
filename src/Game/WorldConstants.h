#pragma once
#include "glm/vec3.hpp"

const float WORLD_SIZE = 25.0f;
const float WORLD_HEIGHT = 10.f;

const float TEXTURE_SIZE = 5. / 2.f;

namespace Coordinate
{
	// Compile time functions
	static constexpr glm::vec3 WorldToLevel(const glm::vec3& coord)
	{
		return glm::vec3(coord.x * WORLD_SIZE, coord.y * WORLD_SIZE,
			coord.z * WORLD_SIZE);
	}

	static constexpr glm::vec3 LevelToWorld(const glm::vec3& coord)
	{
		return glm::vec3(coord.x / WORLD_SIZE, coord.y / WORLD_SIZE,
			coord.z / WORLD_SIZE);
	}
}