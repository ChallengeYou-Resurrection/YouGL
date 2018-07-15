#pragma once

#define _USE_MATH_DEFINES
#include <vector>
#include <glm/gtx/intersect.hpp>
#include <math.h>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>

#include "../Editor/CYObjects/CYObjectProperties.h"
#include "../Editor/CYObjects/CYGeneric.h"
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

		void saveLevel(const std::string& fileName);

		bool cameraCollsion(Camera& camera);

		// For saving/loading binary files
		template <typename Archive>
		void serialize(Archive& archive)
		{
			archive(m_header); // , m_walls);
		}

    private:
        std::vector<Model> m_floorModels;
		GeoOctree m_octree;

        LevelHeader m_header;

		WorldTextures m_textures;
		std::vector<std::shared_ptr<CYGeneric>> m_geometry;
};