#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

#include "../Maths/GlmCommon.h"
#include "Mesh.h"
#include "Model.h"

namespace Primitives
{
	Model createCube(glm::vec3 min, glm::vec3 max, GLenum mode = GL_POLYGON);

	constexpr int sphereSpace = 30;
	constexpr int sphereVertexCount = (90 / sphereSpace) * (360 / sphereSpace) * 4;
	Model createSphere(glm::vec3 origin, float radius, GLint textureID = 0, GLenum mode = GL_QUADS);
}
