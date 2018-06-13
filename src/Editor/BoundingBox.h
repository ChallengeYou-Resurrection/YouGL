#pragma once

#include "../Renderer/Model.h"
#include "../Renderer/Mesh.h"
#include "../Renderer/Renderer.h"

#include "glm/vec3.hpp"

#define RENDER_BOUNDING_BOX true

// For AABB collision
// Used for determining what subdivision an object should go to

class BoundingBox {
public :
	BoundingBox(glm::vec3 min, glm::vec3 max);

	bool checkAABB(const BoundingBox& obj);

	void render(Renderer& renderer);

private:
	glm::vec3 m_vecMin;
	glm::vec3 m_vecMax;

	Model m_staticBox;
};