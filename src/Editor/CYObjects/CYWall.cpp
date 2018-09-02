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

	glm::vec3 min = glm::vec3(startPosition.x,
		((float)floor + geometricHeight.bottom) * WORLD_HEIGHT, startPosition.y);

	glm::vec3 max = glm::vec3(endPosition.x,
		((float)floor + geometricHeight.top) * WORLD_HEIGHT, endPosition.y);

	//if ((endPosition.x - startPosition.x) < 0 || (endPosition.y - startPosition.y) < 0)
	//if (   (startPosition.x == endPosition.x) && (endPosition.y < startPosition.y)
	//	|| (startPosition.y == endPosition.y) && (endPosition.x < startPosition.x))
	int x = 0;
	(endPosition.x > startPosition.x) ? x++ : x--;
	(endPosition.y > startPosition.y) ? x++ : x--;
	//if (x < 0)
		//m_objectAABB = { max, min };
	//else
	//{
	//	if (startPosition.x == endPosition.x || startPosition.y == endPosition.y)
			//m_objectAABB = { min, max };
	//	else 
	//		m_objectAABB = { glm::vec3(endPosition.x + 0.01f,
	//		((float)floor + geometricHeight.bottom) * WORLD_HEIGHT, endPosition.y + 0.01f), glm::vec3(startPosition.x - 0.01f,
	//		((float)floor + geometricHeight.top) * WORLD_HEIGHT, startPosition.y - 0.01f) };
	//}
		
	/*m_objectAABB = { glm::vec3(endPosition.x + 0.01f,
		((float)floor + geometricHeight.bottom) * WORLD_HEIGHT, endPosition.y + 0.01f), glm::vec3(startPosition.x - 0.01f,
		((float)floor + geometricHeight.top) * WORLD_HEIGHT, startPosition.y - 0.01f) };
		*/

	auto pMin = [&](float& x1, float& x2) { return std::min(x1, x2) - 0.1f; };
	auto pMax = [&](float& x1, float& x2) { return std::max(x1, x2) + 0.1f; };
	

	m_objectAABB = {
		glm::vec3(pMin(min.x, max.x),  pMin(min.y, max.y),  pMin(min.z, max.z)),
		glm::vec3(pMax(min.x, max.x), pMax(min.y, max.y), pMax(min.z, max.z))
	};

	m_geometryMesh = std::move(mesh);

	// Generate new collision mesh
	m_collisionMesh.clear();
	CPolygon c_front1({ fVertices[0], fVertices[1], fVertices[3] });
	CPolygon c_front2({ fVertices[1], fVertices[2], fVertices[3] });
	//CPolygon c_front3({ fVertices[3], fVertices[1], fVertices[0] });
	//CPolygon c_front4({ fVertices[3], fVertices[2], fVertices[1] });

	m_collisionMesh.push_back(std::move(c_front1));
	m_collisionMesh.push_back(std::move(c_front2));
	//m_collisionMesh.push_back(std::move(c_front3));
	//m_collisionMesh.push_back(std::move(c_front4));
}

Mesh& CYWall::getMesh()
{
	return m_geometryMesh;
};

MinBoundingBox& CYWall::getAABB()
{
	return m_objectAABB;
}