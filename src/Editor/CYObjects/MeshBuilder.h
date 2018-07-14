#pragma once

#include "../Renderer/Mesh.h"
#include "../Game/WorldTextures.h"
#include "CYMiscObjects.h"

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