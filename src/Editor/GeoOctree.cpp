#include "GeoOctree.h"

GeoOctree::GeoOctree(int octreeSize)
{
    size = octreeSize;
	// Bottom Nodes
	m_subdivisionBB.emplace_back(glm::vec3(0, 0, 0),
		glm::vec3(256 / WORLD_SIZE, 256 / WORLD_SIZE, 256 / WORLD_SIZE));
	m_subdivisionBB.emplace_back(glm::vec3(256 / WORLD_SIZE, 0, 0),
		glm::vec3(512 / WORLD_SIZE, 256 / WORLD_SIZE, 256 / WORLD_SIZE));
	m_subdivisionBB.emplace_back(glm::vec3(0, 0, 256 / WORLD_SIZE),
		glm::vec3(256 / WORLD_SIZE, 256 / WORLD_SIZE, 512 / WORLD_SIZE));
	m_subdivisionBB.emplace_back(glm::vec3(256 / WORLD_SIZE, 0, 256 / WORLD_SIZE),
		glm::vec3(512 / WORLD_SIZE, 256 / WORLD_SIZE, 512 / WORLD_SIZE));

	// Top Nodes
	m_subdivisionBB.emplace_back(glm::vec3(0, 256 / WORLD_SIZE, 0),
		glm::vec3(256 / WORLD_SIZE, 512 / WORLD_SIZE, 256 / WORLD_SIZE));
	m_subdivisionBB.emplace_back(glm::vec3(256 / WORLD_SIZE, 256 / WORLD_SIZE, 0),
		glm::vec3(512 / WORLD_SIZE, 512 / WORLD_SIZE, 256 / WORLD_SIZE));
	m_subdivisionBB.emplace_back(glm::vec3(0, 256 / WORLD_SIZE, 256 / WORLD_SIZE),
		glm::vec3(256 / WORLD_SIZE, 512 / WORLD_SIZE, 512 / WORLD_SIZE));
	m_subdivisionBB.emplace_back(glm::vec3(256 / WORLD_SIZE, 256 / WORLD_SIZE, 256 / WORLD_SIZE),
		glm::vec3(512 / WORLD_SIZE, 512 / WORLD_SIZE, 512 / WORLD_SIZE));
}

/*
void GeoOctree::insertGeometry(std::unique_ptr<EditorObject> obj)
{

}
*/

void GeoOctree::buildOctree() {

}

void GeoOctree::cleanOctree() {

}

void GeoOctree::drawOctree(Renderer & renderer)
{
	// Draw bounding boxes as wireframe
	for (auto& box : m_subdivisionBB)
		box.render(renderer);
}
