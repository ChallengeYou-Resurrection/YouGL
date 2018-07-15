#pragma once

#include <cereal/types/string.hpp>
#include <glm/vec3.hpp>
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
};

class CYGeneric
{
public:
	// Virtual functions

	// Mesh Generation
	virtual void createMesh(const WorldTextures& wTex) = 0;
	virtual Mesh& getMesh() = 0;

protected:
	CYObject type = CYObject::CYGeneric;

	// Used to create models 
	Mesh geometryMesh;

	// Player collision
	std::vector<CPolygon> collisionMesh;

	// For octree placement
	// BoundingBox objectAABB;
};

