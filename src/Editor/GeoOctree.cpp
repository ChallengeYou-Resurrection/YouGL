#include "GeoOctree.h"

GeoOctree::GeoOctree(int octreeSize)
{
    size = octreeSize;
	// Bottom Nodes
	m_subdivisionBB.emplace_back(glm::vec3(0, 0, 0),
		glm::vec3(octreeSize / 2, octreeSize / 2, octreeSize / 2));
	m_subdivisionBB.emplace_back(glm::vec3(octreeSize / 2, 0, 0),
		glm::vec3(octreeSize, octreeSize / 2, octreeSize / 2));
	m_subdivisionBB.emplace_back(glm::vec3(0, 0, octreeSize / 2),
		glm::vec3(octreeSize / 2, octreeSize / 2, octreeSize));
	m_subdivisionBB.emplace_back(glm::vec3(octreeSize / 2, 0, octreeSize / 2),
		glm::vec3(octreeSize, octreeSize / 2, octreeSize));

	// Top Nodes
	m_subdivisionBB.emplace_back(glm::vec3(0, octreeSize / 2, 0),
		glm::vec3(octreeSize / 2, octreeSize, octreeSize / 2));
	m_subdivisionBB.emplace_back(glm::vec3(octreeSize / 2, octreeSize / 2, 0),
		glm::vec3(octreeSize, octreeSize, octreeSize / 2));
	m_subdivisionBB.emplace_back(glm::vec3(0, octreeSize / 2, octreeSize / 2),
		glm::vec3(octreeSize / 2, octreeSize, octreeSize));
	m_subdivisionBB.emplace_back(glm::vec3(octreeSize / 2, octreeSize / 2, octreeSize / 2),
		glm::vec3(octreeSize, octreeSize, octreeSize));
}

/*void GeoOctree::insertGeometry(std::unique_ptr<EditorObject> obj)
{

}*/

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
