#pragma once

#include "../Renderer/Mesh.h"
#include "WorldTextures.h"

struct Wall;

Mesh createMesh(const Wall& wall, const WorldTextures& wTex);