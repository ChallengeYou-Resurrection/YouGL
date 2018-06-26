#pragma once

#include "../Renderer/Mesh.h"
#include "WorldTextures.h"
#include "CYObjects.h"

struct Wall;

namespace MeshBuilder {
	struct WallHeight
	{
		float bottom;
		float top;
	};

	Mesh createMesh(const Wall& wall, const WorldTextures& wTex);

	WallHeight getWallGeometricHeight(const Wall& wall);
}