#pragma once

#include <vector>
#include "CYObjectProperties.h"
#include "CYObjects.h"
#include "WorldTextures.h"
#include "../Editor/GeoOctree.h"
#include "../Renderer/Model.h"
#include "../Renderer/Camera.h"

class Renderer;

class CYGameLevel
{
   public:
        CYGameLevel();

        void loadFromOldFormat(int gameNumber);
        void load(const std::string& fileName);
        void createModels();
        void renderFloors(Renderer& renderer);

		bool cameraCollsion(Camera& camera);

    private:
        std::vector<Model> m_floorModels;
		GeoOctree m_octree;

        LevelHeader m_header;

		WorldTextures m_textures;
        std::vector<Wall> m_walls;
};