#pragma once
#include <glm/vec3.hpp>

constexpr float WORLD_SIZE = 25.0f;
constexpr float WORLD_HEIGHT = 10.f;

constexpr float TEXTURE_SIZE = 5. / 2.f;

namespace Coordinate
{
	// Compile time functions
	static constexpr glm::vec3 WorldToLevel(const glm::vec3& coord)
	{
		return glm::vec3(coord.x * WORLD_SIZE, coord.y * WORLD_SIZE,
			coord.z * WORLD_SIZE);
	}
}