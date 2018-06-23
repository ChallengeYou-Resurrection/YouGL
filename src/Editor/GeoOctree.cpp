#include "GeoOctree.h"

GeoOctree::GeoOctree(int octreeSize)
{
    size = octreeSize;

	// Create a bounding box for the whole build space
	m_boundingBox = std::make_unique<BoundingBox>(glm::vec3(0, 0, 0), 
		glm::vec3(size, size, size));
}

GeoOctree::GeoOctree(int octreeSize, std::unique_ptr<BoundingBox> bb)
{
	size = octreeSize;

	m_boundingBox = std::move(bb);
}

void GeoOctree::subdivide()
{
	if (subdivided)
		return;

	this->subdivided = true;

	// Create bounding boxes for subdivisions 
	// Bottom Nodes
	m_subdivisionBB.emplace_back(glm::vec3(0, 0, 0),
		glm::vec3(size / 2, size / 2, size / 2));
	m_subdivisionBB.emplace_back(glm::vec3(size / 2, 0, 0),
		glm::vec3(size, size / 2, size / 2));
	m_subdivisionBB.emplace_back(glm::vec3(0, 0, size / 2),
		glm::vec3(size / 2, size / 2, size));
	m_subdivisionBB.emplace_back(glm::vec3(size / 2, 0, size / 2),
		glm::vec3(size, size / 2, size));

	// Top Nodes
	m_subdivisionBB.emplace_back(glm::vec3(0, size / 2, 0),
		glm::vec3(size / 2, size, size / 2));
	m_subdivisionBB.emplace_back(glm::vec3(size / 2, size / 2, 0),
		glm::vec3(size, size, size / 2));
	m_subdivisionBB.emplace_back(glm::vec3(0, size / 2, size / 2),
		glm::vec3(size / 2, size, size));
	m_subdivisionBB.emplace_back(glm::vec3(size / 2, size / 2, size / 2),
		glm::vec3(size, size, size));

	// Create nodes and assign the bounding boxes to them
	for (int i = 0; i < 8; i++)
		m_nodes[i] = std::make_unique<GeoOctree>(size / 2, 
			std::make_unique<BoundingBox>(std::move(m_subdivisionBB.at(i))));
}

bool GeoOctree::checkIfWallInsideAABB(const Wall& wall, const glm::vec3& min,
	const glm::vec3& max)
{
	return m_boundingBox->checkAABB(min, max);
}

void GeoOctree::insertWall(std::shared_ptr<Wall> wall_ptr)
{
	m_walls.push_back(wall_ptr);
}

void GeoOctree::buildOctree() {
	std::cout << "Current node has " << m_walls.size() << " walls\n";

	subdivide();

	// Check if each wall can fit into each node
	for (auto& wall : m_walls)
	{
		// Get AABB of the wall
		glm::vec3 min = glm::vec3(wall->startPosition.x, wall->floor * WORLD_HEIGHT,
			wall->startPosition.y);

		glm::vec3 max = glm::vec3(wall->endPosition.x, 
			(wall->floor + wall->height) * WORLD_HEIGHT, wall->endPosition.y);

		for (auto& node : m_nodes)
		{
			if (node->checkIfWallInsideAABB(*wall, min, max))
			{
				node->insertWall(std::move(wall));
			}
		}
	}

	// For debugging
	for (auto& node : m_nodes)
		std::cout << "Node: " << m_walls.size() << " - > " << node->getObjectSize() << "\n";
}

void GeoOctree::cleanOctree() {

}

void GeoOctree::drawOctree(Renderer & renderer)
{
	m_boundingBox->render(renderer);

	// Draw bounding boxes as wireframe
	if (subdivided)
		for (auto& node : m_nodes)
			node->drawOctree(renderer);
}

int GeoOctree::getObjectSize()
{
	return m_walls.size();
}
