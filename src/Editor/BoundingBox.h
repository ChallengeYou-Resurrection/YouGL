#pragma once

#include "../Renderer/Model.h"
#include "../Renderer/Mesh.h"
#include "../Renderer/Renderer.h"

#include "glm/vec3.hpp"
#include "../Game/WorldConstants.h"

#define RENDER_BOUNDING_BOX true

// For AABB collision
// Used for determining what subdivision an object should go to

class BoundingBox {
public :
	BoundingBox(glm::vec3 min, glm::vec3 max);

	bool checkAABB(const BoundingBox& obj);
	bool checkAABB(const glm::vec3& obj_minv3, const glm::vec3& obj_maxv3);

	glm::vec3 getVecMin();
	glm::vec3 getVecMax();

	void render(Renderer& renderer);

private:
	glm::vec3 m_vecMin;
	glm::vec3 m_vecMax;

	Model m_staticBox;
};