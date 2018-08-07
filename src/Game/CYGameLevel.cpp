#include "CYGameLevel.h"

#include <iostream>
#include <fstream>
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>

#include "../Renderer/OpenGLErrorCheck.h"
#include "../Renderer/Mesh.h"
#include "../Renderer/Renderer.h"
#include "../Editor/OldFormat/OldFormatUtil.h"
#include "../Editor/CYObjects/MeshBuilder.h"

// Constructor / Init Objects
CYGameLevel::CYGameLevel(sf::Vector2u screenResolution)
	: m_octree(512)
	, m_editorGui(&m_floor)
	, m_screenRes(screenResolution)
{
	// Test the sphere primitive (TEMP)
	sphere = Primitives::createSphere(glm::vec3(0, 0, 0), 1, m_textures.getTexID());
}

void CYGameLevel::initGUI(nk_context * ctx)
{
	m_editorGui.init(ctx);
	m_debug.init(ctx);
}

void CYGameLevel::initCamera(Renderer & renderer)
{
	renderer.initScene(m_camera);
}

// Load from the Old CY Format (REGEX) from local server
void CYGameLevel::loadFromOldFormat(int gameNumber)
{
	// Use a clock to determine the speed it takes to load a level
	sf::Clock timer;

    auto gameCode = OldFormat::loadFromLocalhost(gameNumber);
    if (!gameCode) {
        std::cout << "Unable to load level " << gameNumber << '\n';
        std::cin.ignore();
    }
    auto gameCodeTable  = OldFormat::getObjectTable(*gameCode);
	m_header			= OldFormat::extractHeader(*gameCode);
	m_geometry			= OldFormat::extractGeometry(gameCodeTable);

    std::cout << "Game    " << m_header.gameName << '\n';
    std::cout << "Author: " << m_header.gameAuthor << '\n';
	std::cout << "Floors: " << std::to_string(m_header.floorCount) << "\n\n";

    for (int i = 0; i < m_header.floorCount; i++) {
        m_floorModels.emplace_back();
    }

	std::cout << "Level #" << gameNumber << " loaded in " << timer.getElapsedTime().asSeconds() << "s\n" << std::endl;
}

// Load the level using the Cereal Library (Much faster)
void CYGameLevel::load(const std::string & fileName)
{
	// Use a clock to determine the speed it takes to load a level
	sf::Clock timer;

    std::ifstream inFile("cy_files/binary/" + fileName, std::ios::binary);
    cereal::BinaryInputArchive archive(inFile);

    archive(*this);

    std::cout << "Game    " << m_header.gameName << '\n';
    std::cout << "Author: " << m_header.gameAuthor << '\n';
	std::cout << "Floors: " << std::to_string(m_header.floorCount) << "\n\n";

    for (int i = 0; i < m_header.floorCount; i++) {
        m_floorModels.emplace_back();
    }

	std::cout << "Level " << fileName << " loaded in " << timer.getElapsedTime().asSeconds() << "s\n" << std::endl;
}

// Save level using the Cereal Library
void CYGameLevel::saveLevel(const std::string & fileName)
{
	try {
		// Create output stream for cereal to use
		std::ofstream os("cy_files/binary/" + fileName, std::ios::binary);
		cereal::BinaryOutputArchive archive(os);

		archive(*this);

		std::cout << "Saved as " << fileName << "\n";
	}
	catch (cereal::Exception& e) {
		std::cout << "Error saving: " << e.what() << std::endl;
	}
}

// Contruct all floors
void CYGameLevel::createModels()
{
	sf::Clock timer;
	std::cout << "Constructing geometry\n";

	// Separate mesh for each floor
	for (int f = 0; f < m_header.floorCount; f++)
	{
		// Keep opaque & transparent meshes apart
		Mesh oFloorMesh;
		Mesh tFloorMesh;

		for (auto& obj : m_geometry) {
			if (obj->getLevel() == (f + 1))
			{
				// Generate Mesh
				obj->createMesh(m_textures);
				m_octree.insertGeometry(obj);

				// Combine
				auto mesh = obj->getMesh();
				oFloorMesh.combineWith(mesh);
			}
		}

		m_floorModels[f].opaqueMesh.create(oFloorMesh, m_textures.getTexID());
	}

	std::cout << "Geometry created in " << timer.getElapsedTime().asSeconds() << "s\n" << std::endl;

	//std::cout << "Vertices : " << masterMesh.vertices.size() << "\n";
	//::cout << "Indices : " << masterMesh.indices.size() << "\n";

	std::cout << "\nConstructing Octree\n";
	m_octree.buildOctree();
    
}

void CYGameLevel::buildFloor(int floor)
{
	// Keep opaque & transparent meshes apart
	Mesh oFloorMesh;
	Mesh tFloorMesh;

	for (auto& obj : m_geometry) {
		if (obj->getLevel() == (floor + 1) && obj != m_selectedObject)
		{
			// Generate Mesh
			obj->createMesh(m_textures);

			// Combine
			auto mesh = obj->getMesh();
			oFloorMesh.combineWith(mesh);
		}
	}

	m_floorModels[floor].opaqueMesh.destroyModel();
	m_floorModels[floor].opaqueMesh.create(oFloorMesh, m_textures.getTexID());
}

// Render all floors
void CYGameLevel::renderFloors(Renderer & renderer)
{
	for (int f = 0; f < m_header.floorCount; f++)
		renderer.draw(m_floorModels[f].opaqueMesh);

	m_octree.drawOctree(renderer);
}

// Renders floors from 0 to a the current floor
void CYGameLevel::partiallyRenderFloors(Renderer & renderer)
{
	for (int f = 0; f < m_floor; f++)
		renderer.draw(m_floorModels[f].opaqueMesh);

	renderer.draw(sphere);

	m_octree.drawOctree(renderer);
}

// Render the Editor GUIs
void CYGameLevel::renderGUIs(Renderer & renderer)
{
	renderer.draw(m_editorGui); // Draw GUI
	renderer.draw(m_debug);
}

void CYGameLevel::input(Controller & controller)
{
	// Move camera according to player input
	m_camera.input(controller);

	m_mousePosition = controller.getMousePositionRelativeToWindow();
}

// Update all variables/data every frame
void CYGameLevel::update(float deltaTime)
{
	// Mouse Ray (test)
	MouseRay::Ray mRay = MouseRay::calculateMouseRay(m_mousePosition, m_screenRes, m_camera);
	m_debug.add3DVector("Ray Origin", mRay.origin);
	m_debug.add3DVector("Ray Direction", mRay.direction);
	
	int n = m_octree.nodesIntersectingRay(mRay);
	m_debug.addMessage("You are looking at " + std::to_string(n) + " nodes");

	std::vector<GeoOctree::NodeDistance> rayNodes = m_octree.getNodesIntersectingRayOrdered(mRay);
	
	// TODO: Put in separate function?
	int objCount = 0;
	std::optional<std::shared_ptr<CYGeneric>> obj;
	for (auto& node : rayNodes)
	{
		objCount += node.second->getObjectSize();

		obj = node.second->getObjectClosestToRay(mRay);
		if (obj != std::nullopt)
		{
			if (obj.value() != m_selectedObject)
			{
				// If the new object is on another floor, rebuild the previous floor 
				if (m_selectedObject != nullptr &&
					obj.value()->getLevel() != m_selectedObject->getLevel())
				{
					int lvl = m_selectedObject->getLevel();
					m_selectedObject = nullptr;
					this->buildFloor(lvl - 1);
				}

				m_selectedObject = obj.value();
	
				this->buildFloor(m_selectedObject->getLevel() - 1);
			}

			break;
		}
		else {
			if (&node == &rayNodes.back())
			{
				if (m_selectedObject != nullptr)
				{
					int lvl = m_selectedObject->getLevel();
					m_selectedObject = nullptr;
					this->buildFloor(lvl - 1);
				}
			}
		}
	}

	if (m_selectedObject != nullptr)
		m_debug.addMessage("Selected object is in the " + std::to_string(m_selectedObject->getLevel()) + " floor.");


	m_debug.addMessage(std::to_string(objCount) + " objects out of " + std::to_string(m_octree.getTotalObjectSize()) + " checked.");

	// GUI Update
	m_editorGui.update(deltaTime);
	m_debug.update(deltaTime);

	// Clamp important variables
	m_floor = std::clamp(m_floor, (u8)0, m_header.floorCount);

	// Collision Detection & Response
	// TODO: Replace w/ better algorithm
	if (!cameraCollision(m_camera))
		m_camera.applyVelocity();

	// Update camera after applying calculations to get accurate view matrix
	m_camera.update(deltaTime);
}

// Deprecated Function, to be replaced with MUCH better collision detection
bool CYGameLevel::cameraCollision(Camera & camera)
{
	// TODO: Clean and move this into GeoOctree class
	// Get start and finish for cam movement
	const glm::vec3 cam_pos = Coordinate::WorldToLevel(camera.getPositon());
	const glm::vec3 cam_end = Coordinate::WorldToLevel(camera.getPositon() + (camera.getVelocity() * 1.2f));

	/*// If there's no velocity, skip
	if (glm::all(glm::equal(cam_pos, cam_end)))
		return false;

	std::vector<std::shared_ptr<Wall>> wall_list = m_octree.getWallVectorNearPoint(cam_pos);

	// Insert more walls 
	if (!m_octree.checkIfTwoPointsInSameOctree(cam_pos, cam_end))
	{
		std::vector<std::shared_ptr<Wall>> extended_wall_list = m_octree.getWallVectorNearPoint(cam_end);
		wall_list.insert(wall_list.end(), extended_wall_list.begin(), extended_wall_list.end());
	}

	//std::cout << "vec size: " << wall_list.size() << "\n";

	// Check all walls for collision
	for (auto& wall : wall_list)
	{
		// Reconstruct to get vertices of wall
		// TODO: More efficient or streamlined way of doing this?
		auto geometricHeight = MeshBuilder::getWallGeometricHeight(*wall);
		float minHeight = ((float)wall->floor + geometricHeight.bottom) * WORLD_HEIGHT;
		float maxHeight = ((float)wall->floor + geometricHeight.top)    * WORLD_HEIGHT;

		glm::vec2 wallOrigin = { (float)wall->startPosition.x, (float)wall->startPosition.y };
		glm::vec2 wallFinish = { (float)wall->endPosition.x, (float)wall->endPosition.y };

		std::array<glm::vec3, 4> vertices;
		vertices[1] = glm::vec3((wallOrigin.x), maxHeight, (wallOrigin.y));
		vertices[2] = glm::vec3((wallFinish.x), maxHeight, (wallFinish.y));
		vertices[3] = glm::vec3((wallFinish.x), minHeight, (wallFinish.y));
		vertices[0] = glm::vec3((wallOrigin.x), minHeight, (wallOrigin.y));

		glm::vec3 normal = glm::cross(vertices[2] - vertices[1], vertices[3] - vertices[1]);

		// Intersection test
		//std::cout << "Triangle point: " << vertices[1].x << ", " << vertices[1].y << ", " << vertices[1].z << "\n";
		glm::vec3 intersection;
		if (glm::intersectLineTriangle(cam_pos, camera.getVelocity(), vertices[0], vertices[2], vertices[1], intersection) ||
			glm::intersectLineTriangle(cam_pos, camera.getVelocity(), vertices[2], vertices[3], vertices[0], intersection))
		{
			//std::cout << "Collision Detected, point: " << intersection.x << ", " << intersection.y << ", " << intersection.z << "\n";

			// Ref: https://mathinsight.org/distance_point_plane
			// This is used to get the distance from the camera to closest point of the colliding mesh
			// Normalise normal vector
			normal = glm::normalize(normal);
			glm::vec3 planeOrigin = vertices[0];

			// Vector plane origin to camera
			glm::vec3 v = glm::vec3(cam_end.x - planeOrigin.x, cam_end.y - planeOrigin.y,
				cam_end.z - planeOrigin.z);

			// Calculate the distance
			float distance = glm::abs(glm::dot(v, normal));

			if (distance < 1.1f)
			{
				glm::vec3 cameraMovement = camera.getVelocity();
				float dotV = glm::dot(glm::normalize(cameraMovement), normal);
				float angle = (M_PI/2.f) - acos(dotV);
				if (dotV > 0)
					angle = (M_PI / 2.f) + acos(dotV);

				camera.setVelocity(glm::abs(cameraMovement)*cos(angle)); 

				std::cout << "Dot: " << dotV << "\n";
				std::cout << "Angle: " << angle * (180/M_PI) << "\n";

				return false;
			}
		}

	}*/

	return false;
}

Camera & CYGameLevel::getCamera()
{
	return m_camera;
}
