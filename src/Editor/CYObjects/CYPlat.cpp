#include "CYPlat.h"

CYPlat::CYPlat(std::smatch & matchGroups)
{
	position = RegexExtractor::extractVector(matchGroups, 1);
	size = (u8)std::stoi(matchGroups[3].str());

	// If group 4 and 5 are empty then it's
	// [X, Y, [Size], Level] (Very old format)
	if (matchGroups[4] == "" && matchGroups[5] == "")
	{
		// Default
		material.textureId = TextureID::Wood;
		material.colour = sf::Color(255, 255, 255);
	}
	else {
		material = RegexExtractor::extractMaterial(matchGroups, 4, RegexExtractor::TextureType::PlatTex);

		// Check if there's a height element
		if (matchGroups[6] != "")
		{
			height = (u8)std::stoi(matchGroups[6].str());
		}
	}

	// Level
	floor = (u8)std::stoi(matchGroups[7].str());
}

void CYPlat::createMesh(const WorldTextures& wTex)
{
	Mesh mesh;
	float pHeight = ((float)floor + MeshBuilder::getPlatGeometricHeight(height)) * WORLD_HEIGHT;
	auto pSize = MeshBuilder::getPlatGeometricSize(size);

	glm::vec2 platMin = { (float)position.x - pSize / 2.f, (float)position.y - pSize / 2.f };
	glm::vec2 platMax = { (float)position.x + pSize / 2.f, (float)position.y + pSize / 2.f };

	std::array<glm::vec3, 4> fVertices;
	fVertices[1] = glm::vec3((platMin.x) / WORLD_SIZE, pHeight / WORLD_SIZE, (platMin.y) / WORLD_SIZE);
	fVertices[2] = glm::vec3((platMax.x) / WORLD_SIZE, pHeight / WORLD_SIZE, (platMin.y) / WORLD_SIZE);
	fVertices[3] = glm::vec3((platMax.x) / WORLD_SIZE, pHeight / WORLD_SIZE, (platMax.y) / WORLD_SIZE);
	fVertices[0] = glm::vec3((platMin.x) / WORLD_SIZE, pHeight / WORLD_SIZE, (platMax.y) / WORLD_SIZE);
	std::array<glm::vec3, 4> bVertices = { fVertices[3], fVertices[2], fVertices[1], fVertices[0] };

	// FRONT FACE
	MeshBuilder::addQuadToMesh(mesh, fVertices, material);
	MeshBuilder::applyPlatTextureCoords(mesh, fVertices, material, wTex);
	
	// BACK FACE
	MeshBuilder::addQuadToMesh(mesh, bVertices, material);
	MeshBuilder::applyPlatTextureCoords(mesh, bVertices, material, wTex);

	m_geometryMesh = std::move(mesh);

	// Create AABB for octree placement
	m_objectAABB = { {platMin.x, pHeight, platMin.y }, { platMax.x, pHeight, platMax.y } };
}

Mesh& CYPlat::getMesh()
{
	return m_geometryMesh;
};

MinBoundingBox& CYPlat::getAABB()
{
	return m_objectAABB;
}

