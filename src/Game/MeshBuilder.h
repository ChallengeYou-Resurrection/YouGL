#pragma once

#include "../Renderer/Mesh.h"
#include "WorldTextures.h"
#include "CYObjects.h"

struct Wall;

Mesh createMesh(const Wall& wall, const WorldTextures& wTex);

namespace {
	struct WallHeight
	{
		float bottom;
		float top;
	};

	WallHeight getWallGeometricHeight(const Wall& wall)
	{
		float bottomHeight = 0.0f;
		float topHeight = 1.0f;

		switch (wall.height) {
		case 2:  topHeight = 3 / 4.0f;  bottomHeight = 0.0f; break;
		case 3:  topHeight = 2 / 4.0f;  bottomHeight = 0.0f; break;
		case 4:  topHeight = 1 / 4.0f;  bottomHeight = 0.0f; break;

		case 5:  topHeight = 2 / 4.0f;  bottomHeight = 1 / 4.0f; break;
		case 6:  topHeight = 3 / 4.0f;  bottomHeight = 2 / 4.0f; break;
		case 7:  topHeight = 4 / 4.0f;  bottomHeight = 3 / 4.0f; break;

		case 8:  topHeight = 4 / 4.0f;  bottomHeight = 2 / 4.0f; break;
		case 9:  topHeight = 4 / 4.0f;  bottomHeight = 1 / 4.0f; break;
		case 10: topHeight = 3 / 4.0f;  bottomHeight = 1 / 4.0f; break;
		default: topHeight = 4 / 4.0f;  bottomHeight = 0.0f; break;
		}
		return {
			bottomHeight, topHeight
		};
	}
}