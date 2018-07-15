#include "CYWall.h"

CYWall::CYWall(std::smatch & matchGroups)
{
	auto displacement = RegexExtractor::extractVector(matchGroups, 1);
	startPosition = RegexExtractor::extractVector(matchGroups, 3);
	endPosition = { displacement.x + startPosition.x,
		displacement.y + startPosition.y };

	//Texture
	frontMaterial = RegexExtractor::extractMaterial(matchGroups, 5);
	backMaterial = RegexExtractor::extractMaterial(matchGroups, 7);

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

	std::array<glm::vec3, 4> vertices;
	vertices[1] = glm::vec3((wallOrigin.x) / WORLD_SIZE, maxHeight / WORLD_SIZE, (wallOrigin.y) / WORLD_SIZE);
	vertices[2] = glm::vec3((wallFinish.x) / WORLD_SIZE, maxHeight / WORLD_SIZE, (wallFinish.y) / WORLD_SIZE);
	vertices[3] = glm::vec3((wallFinish.x) / WORLD_SIZE, minHeight / WORLD_SIZE, (wallFinish.y) / WORLD_SIZE);
	vertices[0] = glm::vec3((wallOrigin.x) / WORLD_SIZE, minHeight / WORLD_SIZE, (wallOrigin.y) / WORLD_SIZE);

	glm::vec3 normal = glm::cross(vertices[2] - vertices[1], vertices[3] - vertices[1]);

	//Vertices
	mesh.vertices.insert(mesh.vertices.end(), { vertices[1].x, vertices[1].y, vertices[1].z });
	mesh.vertices.insert(mesh.vertices.end(), { vertices[2].x, vertices[2].y, vertices[2].z });
	mesh.vertices.insert(mesh.vertices.end(), { vertices[3].x, vertices[3].y, vertices[3].z });
	mesh.vertices.insert(mesh.vertices.end(), { vertices[0].x, vertices[0].y, vertices[0].z });

	//Normals
	for (int i = 0; i < 4; i++) {
		mesh.normals.insert(mesh.normals.end(), { normal.x, normal.y, normal.z });
	}

	//Colours
	for (int i = 0; i < 4; i++) {
		mesh.colour.insert(mesh.colour.end(), {
			(float)frontMaterial.colour.r / 255.0f,
			(float)frontMaterial.colour.g / 255.0f,
			(float)frontMaterial.colour.b / 255.0f
			});
	}

	//Textre Coords
	float length = sqrt(pow(wallFinish.y - wallOrigin.y, 2) + pow(wallFinish.x - wallOrigin.x, 2));
	float x_2d = length / WORLD_SIZE;
	const sf::Vector2f tSize = wTex.getTextureScale(frontMaterial.textureId);

	mesh.texCoords.insert(mesh.texCoords.end(), { 0		* TEXTURE_SIZE * tSize.x, vertices[2].y *TEXTURE_SIZE * tSize.y, (float)frontMaterial.textureId });
	mesh.texCoords.insert(mesh.texCoords.end(), { x_2d	* TEXTURE_SIZE * tSize.x, vertices[2].y *TEXTURE_SIZE * tSize.y, (float)frontMaterial.textureId });
	mesh.texCoords.insert(mesh.texCoords.end(), { x_2d	* TEXTURE_SIZE * tSize.x, vertices[0].y *TEXTURE_SIZE * tSize.y, (float)frontMaterial.textureId });
	mesh.texCoords.insert(mesh.texCoords.end(), { 0		* TEXTURE_SIZE * tSize.x, vertices[0].y *TEXTURE_SIZE * tSize.y, (float)frontMaterial.textureId });

	mesh.indices = {
		0, 1, 3, 1, 2, 3
	};

	this->geometryMesh = std::move(mesh);
}

Mesh& CYWall::getMesh()
{
	return geometryMesh;
};
