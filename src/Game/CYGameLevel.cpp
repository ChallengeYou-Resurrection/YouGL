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

CYGameLevel::CYGameLevel()
	: m_octree(512)
{ }

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
	std::cout << "Floors:  " << m_header.floorCount << "\n\n";

    for (int i = 0; i < m_header.floorCount; i++) {
        m_floorModels.emplace_back();
    }

	std::cout << "Level #" << gameNumber << " loaded in " << timer.getElapsedTime().asSeconds() << "s\n" << std::endl;
}

void CYGameLevel::load(const std::string & fileName)
{
	// Use a clock to determine the speed it takes to load a level
	sf::Clock timer;

    std::ifstream inFile("cy_files/binary/" + fileName, std::ios::binary);
    cereal::BinaryInputArchive archive(inFile);

    archive(*this);

    std::cout << "Game    " << m_header.gameName << '\n';
    std::cout << "Author: " << m_header.gameAuthor << '\n';
	std::cout << "Floors:  " << m_header.floorCount << "\n\n";

    for (int i = 0; i < m_header.floorCount; i++) {
        m_floorModels.emplace_back();
    }

	std::cout << "Level " << fileName << " loaded in " << timer.getElapsedTime().asSeconds() << "s\n" << std::endl;
}

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

void CYGameLevel::createModels()
{
	std::cout << "Constructing geometry\n";

    Mesh masterMesh;
    for (auto& obj : m_geometry) {
		//std::shared_ptr<Wall> wall_ptr = std::make_shared<Wall>(wall);
		//m_octree.insertWall(wall_ptr);

        //auto mesh = MeshBuilder::createMesh(wall, m_textures);
		obj->createMesh(m_textures);
		auto mesh = obj->getMesh();
        masterMesh.combineWith(mesh);
       // models.emplace_back(mesh);
    }

	std::cout << "Vertices : " << masterMesh.vertices.size() << "\n";
	std::cout << "Indices : " << masterMesh.indices.size() << "\n";

	std::cout << "\nConstructing Octree\n";
	m_octree.buildOctree();
    m_floorModels[0].create(masterMesh, m_textures.getTexID());
}

void CYGameLevel::renderFloors(Renderer & renderer)
{
    renderer.draw(m_floorModels[0]);
	m_octree.drawOctree(renderer);
}

bool CYGameLevel::cameraCollsion(Camera & camera)
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
