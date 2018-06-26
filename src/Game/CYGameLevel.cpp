#include "CYGameLevel.h"

#include <iostream>
#include <fstream>
#include <cereal/cereal.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>

#include "../Renderer/OpenGLErrorCheck.h"
#include "../Renderer/Mesh.h"
#include "../Renderer/Renderer.h"
#include "OldFormat/OldFormatUtil.h"
#include "MeshBuilder.h"

CYGameLevel::CYGameLevel()
	: m_octree(512)
{ }

void CYGameLevel::loadFromOldFormat(int gameNumber)
{
    auto gameCode = OldFormat::loadFromWebsite(gameNumber);
    if (!gameCode) {
        std::cout << "Unable to load level " << gameNumber << '\n';
        std::cin.ignore();
    }
    auto gameCodeTable  = OldFormat::getObjectTable(*gameCode);
    m_header            = OldFormat::extractHeader(*gameCode);
    m_walls             = OldFormat::extractWalls(gameCodeTable.at("walls"));

    std::cout << "Game    " << m_header.gameName << '\n';
    std::cout << "Author: " << m_header.gameAuthor << '\n';
    std::cout << "Floors:  " << m_header.floorCount << '\n';
    std::cout << "Walls: " << m_walls.size() << '\n';

    for (int i = 0; i < m_header.floorCount; i++) {
        m_floorModels.emplace_back();
    }
}

void CYGameLevel::load(const std::string & fileName)
{
    std::ifstream inFile("cy_files/binary/" + fileName);
    cereal::BinaryInputArchive archive(inFile);

    archive(m_header, m_walls);

    std::cout << "Game    " << m_header.gameName << '\n';
    std::cout << "Author: " << m_header.gameAuthor << '\n';
    std::cout << "Floors:  " << m_header.floorCount << '\n';
    std::cout << "Walls: " << m_walls.size() << '\n';

    for (int i = 0; i < m_header.floorCount; i++) {
        m_floorModels.emplace_back();
    }
}

void CYGameLevel::createModels()
{
    Mesh masterMesh;
    for (auto& wall : m_walls) {
		std::shared_ptr<Wall> wall_ptr = std::make_shared<Wall>(wall);
		m_octree.insertWall(wall_ptr);

        auto mesh = createMesh(wall, m_textures);
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
	const glm::vec3 cam_end = Coordinate::WorldToLevel(camera.getPositon() + (camera.getVelocity() * 1.f));
	
	// If there's no velocity, skip
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
		auto geometricHeight = getWallGeometricHeight(*wall);
		float minHeight = ((float)wall->floor + geometricHeight.bottom) * WORLD_HEIGHT;
		float maxHeight = ((float)wall->floor + geometricHeight.top)    * WORLD_HEIGHT;

		glm::vec2 wallOrigin = { (float)wall->startPosition.x, (float)wall->startPosition.y };
		glm::vec2 wallFinish = { (float)wall->endPosition.x, (float)wall->endPosition.y };

		std::array<glm::vec3, 4> vertices;
		vertices[1] = glm::vec3((wallOrigin.x), maxHeight, (wallOrigin.y));
		vertices[2] = glm::vec3((wallFinish.x), maxHeight, (wallFinish.y));
		vertices[3] = glm::vec3((wallFinish.x), minHeight, (wallFinish.y));
		vertices[0] = glm::vec3((wallOrigin.x), minHeight, (wallOrigin.y));

		// Intersection test
		//std::cout << "Triangle point: " << vertices[1].x << ", " << vertices[1].y << ", " << vertices[1].z << "\n";
		glm::vec3 intersection;
		if (glm::intersectLineTriangle(cam_pos, camera.getVelocity(), vertices[0], vertices[2], vertices[1], intersection) ||
			glm::intersectLineTriangle(cam_pos, camera.getVelocity(), vertices[2], vertices[3], vertices[0], intersection))
		{
			//std::cout << "Collision Detected, point: " << intersection.x << ", " << intersection.y << ", " << intersection.z << "\n";
			
			/*
			// GLM returns a barycentric coordinate, we need to convert to cartesian
			// in order to calculate the distance / magnitude
			glm::vec3 cart = intersection.x * vertices[1] + intersection.y * vertices[2] + intersection.z * vertices[0];
			std::cout << "Collision Detected, cartesian point: " << cart.x << ", " << cart.y << ", " << cart.z << "\n";
			*/

			if (intersection.x < 200 && intersection.x > 0)
				return true;
		}

		//return (glm::intersectLineTriangle(cam_pos, cam_end, vertices[1], vertices[2], vertices[0], intersection) ||
		//	glm::intersectLineTriangle(cam_pos, cam_end, vertices[1], vertices[2], vertices[0], intersection));
	}

	return false;
}
