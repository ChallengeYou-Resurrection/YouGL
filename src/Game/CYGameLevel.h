#pragma once

#define _USE_MATH_DEFINES
#include <vector>
#include "../Maths/GlmCommon.h"
#include <math.h>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>

#include "../Editor/CYObjects/CYObjectProperties.h"
#include "../Editor/CYObjects/CYGeneric.h"
#include "WorldTextures.h"
#include "../Input/Controller.h"
#include "../Editor/GeoOctree.h"
#include "../Util/MouseRay.h"
#include "../Renderer/Model.h"
#include "../Editor/EditorView.h"
#include "../Editor/Grid.h"

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
        CYGameLevel(sf::Vector2u screenResolution);
		void initGUI(nk_context *ctx);
		void initCamera(Renderer& renderer);

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
		void input(Controller& controller);
		void update(float deltaTime);

		// Geometry Creation
        void createModels();

		// Rendering Functions
        void renderFloors(Renderer& renderer);
		void partiallyRenderFloors(Renderer & renderer);
		void renderGUIs(Renderer& renderer);
		void renderGeneric(Renderer& renderer);
		
		// Misc ?
		bool cameraCollision(Camera& camera);
		//int getObjectSize(); // Return how many objects there are in the world

		// Getter functions
		Camera& getCamera();
		u8 getFloor() { return m_floor; }

    private:
		// Editor 
		EditorView m_camera;
		std::shared_ptr<CYGeneric> m_selectedObject;

		// Level Floors
		void buildFloor(int floor, bool cacheMesh = false);
		void rebuildWithoutReMeshing(int floor, bool cacheMesh = false);
		bool rebuildFromCache(int floor);

		bool selectObjectFromMouse();

		// Level Data
        std::vector<Floor> m_floorModels;
		std::vector<std::shared_ptr<CYGeneric>> m_geometry;
		GeoOctree m_octree;
		Mesh cached_FloorMesh;

        LevelHeader m_header;
		WorldTextures m_textures;

		// GUI
		EditorGUI m_editorGui;
		DebugLogGUI m_debug;

		// Editor Variables
		u8 m_floor = (u8)0;

		// Misc
		sf::Vector2u m_screenRes;
		sf::Vector2i m_mousePosition;

		Model sphere;
		Grid m_levelGrid;
};