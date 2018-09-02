#pragma once

#include "../Maths/GlmCommon.h"
#include "glm/gtx/norm.hpp"

#include "../Game/WorldConstants.h"

#include <iostream>

typedef unsigned int uint32;
#define collision_in(a) ((uint32&) a)

namespace Collision
{
	namespace eSpace
	{
		// Given coordinates, check if they are inside of the triangle
		// Code written by Keidy from Mr-Gamemaker,
		// it is included on Kasper Fauerby's collision detection paper

		bool checkPointInTriangle(const glm::vec3& point, const glm::vec3& pa,
			const glm::vec3& pb, const glm::vec3& pc);

		glm::vec3 covertToESpace(const glm::vec3& vec);

		bool getLowestRoot(float a, float b, float c, float maxR, float* newT);
	}
}