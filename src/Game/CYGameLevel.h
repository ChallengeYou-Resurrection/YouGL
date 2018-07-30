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

#include "../GUI/EditorGUI.h"
#include "../GUI/DebugLogGUI.h"

class Renderer;

struct Floor {
	Model opaqueMesh;
	Model transparentMesh;
};

class CYGameLevel
{
   public:
        CYGameLevel();
		void initGUI(nk_context *ctx);

		// Serializing Functions
        void loadFromOldFormat(int gameNumber);
        void load(const std::string& fileName);
		void saveLevel(const std::string& fileName);

		// For saving/loading binary files
		template <typename Archive>
		void serialize(Archive& archive)
		{
			archive(m_header); // , m_walls);
		}

		// Update functions
		void update(float deltaTime);

		// Geometry Creation
        void createModels();

		// Rendering Functions
        void renderFloors(Renderer& renderer);
		void partiallyRenderFloors(Renderer & renderer);
		void renderGUIs(Renderer& renderer);
		
		// Misc ?
		bool cameraCollision(Camera& camera);
		//int getObjectSize(); // Return how many objects there are in the world

    private:
		// Level Data
        std::vector<Floor> m_floorModels;
		std::vector<std::shared_ptr<CYGeneric>> m_geometry;
		GeoOctree m_octree;

        LevelHeader m_header;
		WorldTextures m_textures;

		// GUI
		EditorGUI m_editorGui;
		DebugLogGUI m_debug;

		// Editor Variables
		u8 m_floor = (u8)0;
};