#include "GeoOctree.h"

GeoOctree::GeoOctree(int octreeSize)
{
    size = octreeSize;
    m_subdivisionBB.emplace_back(glm::vec3(0, 0, 0), glm::vec3(40, 40, 40));
    m_subdivisionBB.emplace_back(glm::vec3(0, 0, 0), glm::vec3(40, 40, 40));
}

void GeoOctree::insertGeometry(std::unique_ptr<EditorObject> obj)
{

}

void GeoOctree::buildOctree() {

}

void GeoOctree::cleanOctree() {

}

void GeoOctree::drawOctree(Renderer & renderer)
{
	// Draw bounding boxes as wireframe
	m_subdivisionBB.at(1).render(renderer);
}
