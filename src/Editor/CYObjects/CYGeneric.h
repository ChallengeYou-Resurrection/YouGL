#pragma once

#include <cereal/types/string.hpp>
#include "../Maths/GlmCommon.h"
#include <vector>
#include <regex>

#include "../BoundingBox.h"
#include "../Renderer/Mesh.h"
#include "../Game/WorldTextures.h"
#include "CYMiscObjects.h"
#include "CYObjectProperties.h"

enum class CYObject {
	CYWall,
	CYPlat,

	CYGeneric
};

struct CPolygon {
	glm::vec3 vertex[3];
	glm::vec3 normal;
	double d;
	CPolygon(std::vector<glm::vec3>&& v)
	{
		vertex[0] = v.at(0); vertex[1] = v.at(1); vertex[2] = v.at(2);
		normal = glm::normalize(glm::cross(v[1] - v[0], v[2] - v[0]));
		d = -(normal.x*vertex[0].x + normal.y*vertex[0].y + normal.z*vertex[0].z);
	}
};

class CYGeneric
{
public:
	// Virtual functions

	// Mesh Generation
	virtual void createMesh(const WorldTextures& wTex) = 0;

	virtual Mesh& getMesh() = 0;
	virtual MinBoundingBox& getAABB() = 0;
	const std::vector<CPolygon>& getCollisionMesh() { return m_collisionMesh; };

	// Properties
	virtual u8 getLevel() = 0;

protected:
	CYObject type = CYObject::CYGeneric;

	// Used to create models 
	Mesh m_geometryMesh;

	// Player collision
	std::vector<CPolygon> m_collisionMesh;

	// For octree placement
	MinBoundingBox m_objectAABB;
};

