#include "CYWall.h"

CYWall::CYWall(std::smatch & matchGroups)
{
	auto displacement = RegexExtractor::extractVector(matchGroups, 1);
	startPosition = RegexExtractor::extractVector(matchGroups, 3);
	endPosition = { displacement.x + startPosition.x,
		displacement.y + startPosition.y };

	//Texture
	frontMaterial = RegexExtractor::extractMaterial(matchGroups, 5, RegexExtractor::TextureType::WallTex);
	backMaterial = RegexExtractor::extractMaterial(matchGroups, 7, RegexExtractor::TextureType::WallTex);

	//Height and floor
	if (matchGroups[10] != "") {
		height = (u8)std::stoi(matchGroups[9].str());
		floor = (u8)std::stoi(matchGroups[10].str());
	}
	else {//Old versions have no wall height
		height = 1;
		floor = (u8)std::stoi(matchGroups[9].str());
	}
}

void CYWall::createMesh(const WorldTextures& wTex)
{
	Mesh mesh;
	auto geometricHeight = MeshBuilder::getWallGeometricHeight(height);

	//Do some geometric calculations (maths done by Ruixel)
	float minHeight = ((float)floor + geometricHeight.bottom) * WORLD_HEIGHT;
	float maxHeight = ((float)floor + geometricHeight.top)    * WORLD_HEIGHT;

	glm::vec2 wallOrigin = { (float)startPosition.x, (float)startPosition.y };
	glm::vec2 wallFinish = { (float)endPosition.x, (float)endPosition.y };
	float length = sqrt(pow(wallFinish.y - wallOrigin.y, 2) + pow(wallFinish.x - wallOrigin.x, 2));

	std::array<glm::vec3, 4> fVertices;
	fVertices[1] = glm::vec3((wallOrigin.x) / WORLD_SIZE, maxHeight / WORLD_SIZE, (wallOrigin.y) / WORLD_SIZE);
	fVertices[2] = glm::vec3((wallFinish.x) / WORLD_SIZE, maxHeight / WORLD_SIZE, (wallFinish.y) / WORLD_SIZE);
	fVertices[3] = glm::vec3((wallFinish.x) / WORLD_SIZE, minHeight / WORLD_SIZE, (wallFinish.y) / WORLD_SIZE);
	fVertices[0] = glm::vec3((wallOrigin.x) / WORLD_SIZE, minHeight / WORLD_SIZE, (wallOrigin.y) / WORLD_SIZE);
	std::array<glm::vec3, 4> bVertices = { fVertices[3], fVertices[2], fVertices[1], fVertices[0] };

	// FRONT FACE
	MeshBuilder::addQuadToMesh(mesh, fVertices, frontMaterial);
	MeshBuilder::applyWallTextureCoords(mesh, fVertices, length, frontMaterial, wTex);

	// BACK FACE
	MeshBuilder::addQuadToMesh(mesh, bVertices, backMaterial);
	MeshBuilder::applyWallTextureCoords(mesh, bVertices, length, backMaterial, wTex);

	this->geometryMesh = std::move(mesh);
}

Mesh& CYWall::getMesh()
{
	return geometryMesh;
};
