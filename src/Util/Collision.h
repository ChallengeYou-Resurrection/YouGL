#pragma once

#include "../Maths/GlmCommon.h"

namespace Collision
{
	// Functions that work in the Epsilloid Space as described by Kasper Fauerby
	// Reference used: http://www.peroxide.dk/papers/collision/collision.pdf
	namespace eSpace
	{
		// Takes in a ray and a plane in epsilloid space and returns the distance to the plane
		// If no intersection takes place, it return -1.0
		double intersectRayPlane(const glm::vec3& rayOrigin, const glm::vec3& rayDirection,
			const glm::vec3& planeOrigin, const glm::vec3& planeNormal);
	}
}