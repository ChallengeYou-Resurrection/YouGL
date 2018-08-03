#pragma once

#include "glm\common.hpp"
#include "Mesh.h"
#include "Model.h"

namespace Primitives
{
	Model createCube(glm::vec3 min, glm::vec3 max, GLenum mode = GL_POLYGON);

	//Mesh createSphere(glm::vec3 origin, float radius);
}
