#include "CYGameLevel.h"

#include <iostream>
#include "../Renderer/Mesh.h"
#include "../Renderer/Renderer.h"
#include "MeshBuilder.h"
#include "OldFormatUtil.h"
#include "../Renderer/OpenGLErrorCheck.h"

CYGameLevel::CYGameLevel()
{
}

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

void CYGameLevel::createModels()
{
    Mesh masterMesh;
    for (auto& wall : m_walls) {
        auto mesh = createMesh(wall);
        masterMesh.combineWith(mesh);
       // models.emplace_back(mesh);
    }
    m_floorModels[0].create(masterMesh);
}

void CYGameLevel::renderFloors(Renderer & renderer)
{
    renderer.draw(m_floorModels[0]);
}
