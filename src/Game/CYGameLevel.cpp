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
    std::cout << "Floors  " << m_header.floorCount << '\n';
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
    std::cout << "Floors  " << m_header.floorCount << '\n';
    std::cout << "Walls: " << m_walls.size() << '\n';

    for (int i = 0; i < m_header.floorCount; i++) {
        m_floorModels.emplace_back();
    }
}

void CYGameLevel::createModels()
{
    Mesh masterMesh;
    for (auto& wall : m_walls) {
        auto mesh = createMesh(wall, m_textures);
        masterMesh.combineWith(mesh);
       // models.emplace_back(mesh);
    }

	std::cout << "Vertices : " << masterMesh.vertices.size() << "/n";
	std::cout << "Indices : " << masterMesh.indices.size() << "/n";

    m_floorModels[0].create(masterMesh, m_textures.getTexID());
}

void CYGameLevel::renderFloors(Renderer & renderer)
{
    renderer.draw(m_floorModels[0]);
}
