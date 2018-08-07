#pragma once

#include "../Renderer/Model.h"
#include "../Renderer/Mesh.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/Primitives.h"

#include "../Maths/GlmCommon.h"
#include "../Game/WorldConstants.h"
#include "../Util/MouseRay.h"

const float RENDER_BOUNDING_BOX = true;

// For AABB collision
// Used for determining what subdivision an object should go to

// Very basic bounding box, contains no functions
struct MinBoundingBox {
	glm::vec3 m_vecMin;
	glm::vec3 m_vecMax;

	// Creation
	MinBoundingBox() {};
	MinBoundingBox(glm::vec3 min, glm::vec3 max)
		: m_vecMin(min)
		, m_vecMax(max)
	{}
};

class BoundingBox {
public :
	BoundingBox(glm::vec3 min, glm::vec3 max);

	const bool checkAABB(const BoundingBox& obj);
	const bool checkAABB(const glm::vec3& obj_minv3, const glm::vec3& obj_maxv3);
	const bool checkPoint(const glm::vec3& point);

	const std::optional<float> checkRayCast(const MouseRay::Ray& ray, float t0, float t1);

	const glm::vec3& getVecMin();
	const glm::vec3& getVecMax();

	void render(Renderer& renderer);

private:
	glm::vec3 m_vecMin;
	glm::vec3 m_vecMax;

	Model m_staticBox;
};