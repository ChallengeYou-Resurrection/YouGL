#pragma once

#include "GlmCommon.h"

namespace Maths
{
	static glm::vec3 lerp(const glm::vec3& v1, const glm::vec3& v2, float alpha)
	{
		return v1 * alpha + v2 * (1.f - alpha);
	}
}