#pragma once

#include <array>
#include <iostream>
#include <iomanip>
#include <algorithm>

#include "../Maths/GlmCommon.h"
#include "CYMiscObjects.h"
#include "../Game/WorldConstants.h"
#include "../Renderer/Mesh.h"
#include "CYMiscObjects.h"
#include "../Game/WorldTextures.h"

struct Wall;

namespace MeshBuilder {
	struct WallHeight
	{
		float bottom;
		float top;
	};

	void addQuadToMesh(Mesh& mesh, const std::array<glm::vec3, 4>& vertices, 
		const Property::Material& mat);

	WallHeight getWallGeometricHeight(const u8 zIndex);

	float getPlatGeometricHeight(const u8 zIndex);
	short getPlatGeometricSize(const u8 size);
	void applyPlatTextureCoords(Mesh& mesh, const std::array<glm::vec3, 4>& vertices,
		const Property::Material& mat, const WorldTextures& wTex);
}