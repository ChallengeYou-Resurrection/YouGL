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
		material = RegexExtractor::extractMaterial(matchGroups, 4);

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

	std::array<glm::vec3, 4> vertices;
	vertices[1] = glm::vec3((platMin.x) / WORLD_SIZE, pHeight / WORLD_SIZE, (platMin.y) / WORLD_SIZE);
	vertices[2] = glm::vec3((platMax.x) / WORLD_SIZE, pHeight / WORLD_SIZE, (platMin.y) / WORLD_SIZE);
	vertices[3] = glm::vec3((platMax.x) / WORLD_SIZE, pHeight / WORLD_SIZE, (platMax.y) / WORLD_SIZE);
	vertices[0] = glm::vec3((platMin.x) / WORLD_SIZE, pHeight / WORLD_SIZE, (platMax.y) / WORLD_SIZE);

	glm::vec3 normal = glm::cross(vertices[2] - vertices[1], vertices[3] - vertices[1]);

	// FRONT FACE
	//Vertices
	mesh.vertices.insert(mesh.vertices.end(), { vertices[0].x, vertices[0].y, vertices[0].z });
	mesh.vertices.insert(mesh.vertices.end(), { vertices[3].x, vertices[3].y, vertices[3].z });
	mesh.vertices.insert(mesh.vertices.end(), { vertices[2].x, vertices[2].y, vertices[2].z });
	mesh.vertices.insert(mesh.vertices.end(), { vertices[1].x, vertices[1].y, vertices[1].z });

	//Normals
	for (int i = 0; i < 4; i++) {
		mesh.normals.insert(mesh.normals.end(), { normal.x, normal.y, normal.z });
	}

	//Colours
	for (int i = 0; i < 4; i++) {
		mesh.colour.insert(mesh.colour.end(), {
			(float)material.colour.r / 255.0f,
			(float)material.colour.g / 255.0f,
			(float)material.colour.b / 255.0f
			});
	}

	sf::Vector2f tSize = wTex.getTextureScale(material.textureId);

	mesh.texCoords.insert(mesh.texCoords.end(), { vertices[0].x * TEXTURE_SIZE * tSize.x, vertices[0].z *TEXTURE_SIZE * tSize.y, (float)material.textureId });
	mesh.texCoords.insert(mesh.texCoords.end(), { vertices[3].x	* TEXTURE_SIZE * tSize.x, vertices[3].z *TEXTURE_SIZE * tSize.y, (float)material.textureId });
	mesh.texCoords.insert(mesh.texCoords.end(), { vertices[2].x	* TEXTURE_SIZE * tSize.x, vertices[2].z *TEXTURE_SIZE * tSize.y, (float)material.textureId });
	mesh.texCoords.insert(mesh.texCoords.end(), { vertices[1].x * TEXTURE_SIZE * tSize.x, vertices[1].z *TEXTURE_SIZE * tSize.y, (float)material.textureId });


	// BACK FACE
	//Vertices
	mesh.vertices.insert(mesh.vertices.end(), { vertices[1].x, vertices[1].y, vertices[1].z });
	mesh.vertices.insert(mesh.vertices.end(), { vertices[2].x, vertices[2].y, vertices[2].z });
	mesh.vertices.insert(mesh.vertices.end(), { vertices[3].x, vertices[3].y, vertices[3].z });
	mesh.vertices.insert(mesh.vertices.end(), { vertices[0].x, vertices[0].y, vertices[0].z });

	//Normals
	normal = -normal;
	for (int i = 0; i < 4; i++) {
		mesh.normals.insert(mesh.normals.end(), { normal.x, normal.y, normal.z });
	}

	//Colours
	for (int i = 0; i < 4; i++) {
		mesh.colour.insert(mesh.colour.end(), {
			(float)material.colour.r / 255.0f,
			(float)material.colour.g / 255.0f,
			(float)material.colour.b / 255.0f
			});
	}
	
	// Texture Coords
	mesh.texCoords.insert(mesh.texCoords.end(), { vertices[1].x * TEXTURE_SIZE * tSize.x, vertices[1].z *TEXTURE_SIZE * tSize.y, (float)material.textureId });
	mesh.texCoords.insert(mesh.texCoords.end(), { vertices[2].x	* TEXTURE_SIZE * tSize.x, vertices[2].z *TEXTURE_SIZE * tSize.y, (float)material.textureId });
	mesh.texCoords.insert(mesh.texCoords.end(), { vertices[3].x	* TEXTURE_SIZE * tSize.x, vertices[3].z *TEXTURE_SIZE * tSize.y, (float)material.textureId });
	mesh.texCoords.insert(mesh.texCoords.end(), { vertices[0].x * TEXTURE_SIZE * tSize.x, vertices[0].z *TEXTURE_SIZE * tSize.y, (float)material.textureId });

	mesh.indices = {
		0, 1, 3, 1, 2, 3, 4, 5, 7, 5, 6, 7
	};

	geometryMesh = std::move(mesh);
}

Mesh& CYPlat::getMesh()
{
	return geometryMesh;
};
