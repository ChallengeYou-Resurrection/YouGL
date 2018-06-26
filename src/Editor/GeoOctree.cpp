#include "GeoOctree.h"

GeoOctree::GeoOctree(int octreeSize)
	: size(octreeSize)
	, m_origin({0,0,0})
{
	// Create a bounding box for the whole build space
	m_boundingBox = std::make_unique<BoundingBox>(glm::vec3(0, 0, 0), 
		glm::vec3(size, size, size));
}

GeoOctree::GeoOctree(int octreeSize, std::unique_ptr<BoundingBox> bb,
	const glm::vec3& origin)
	: size(octreeSize)
	, m_origin(origin)
{
	m_boundingBox = std::move(bb);
}

bool GeoOctree::subdivide()
{
	// If there are any issues, return false
	if (subdivided)
		return false;

	// Check if theres enough items for subdivision to be worth it
	if (m_walls.size() < MAX_ITEMS_PER_OCTREE)
		return false;

	// Check if we can subdivide further (no decimal)
	if (size % 2 == 1)
		return false;

	this->subdivided = true;

	// Create bounding boxes for subdivisions 
	// Bottom Nodes
	m_subdivisionBB.emplace_back(glm::vec3(0, 0, 0) + m_origin,
		glm::vec3(size / 2, size / 2, size / 2) + m_origin);
	m_subdivisionBB.emplace_back(glm::vec3(size / 2, 0, 0) + m_origin,
		glm::vec3(size, size / 2, size / 2) + m_origin);
	m_subdivisionBB.emplace_back(glm::vec3(0, 0, size / 2) + m_origin,
		glm::vec3(size / 2, size / 2, size) + m_origin);
	m_subdivisionBB.emplace_back(glm::vec3(size / 2, 0, size / 2) + m_origin,
		glm::vec3(size, size / 2, size) + m_origin);

	// Top Nodes
	m_subdivisionBB.emplace_back(glm::vec3(0, size / 2, 0) + m_origin,
		glm::vec3(size / 2, size, size / 2) + m_origin);
	m_subdivisionBB.emplace_back(glm::vec3(size / 2, size / 2, 0) + m_origin,
		glm::vec3(size, size, size / 2) + m_origin);
	m_subdivisionBB.emplace_back(glm::vec3(0, size / 2, size / 2) + m_origin,
		glm::vec3(size / 2, size, size) + m_origin);
	m_subdivisionBB.emplace_back(glm::vec3(size / 2, size / 2, size / 2) + m_origin,
		glm::vec3(size, size, size) + m_origin);

	// Create nodes and assign the bounding boxes to them
	for (int i = 0; i < 8; i++)
		m_nodes[i] = std::make_unique<GeoOctree>(size / 2, 
			std::make_unique<BoundingBox>(std::move(m_subdivisionBB.at(i))),
			m_subdivisionBB.at(i).getVecMin());

	// Success
	return true;
}

bool GeoOctree::checkIfWallInsideAABB(const Wall& wall, const glm::vec3& min,
	const glm::vec3& max) const
{
	return m_boundingBox->checkAABB(min, max);
}

void GeoOctree::insertWall(std::shared_ptr<Wall> wall_ptr)
{
	m_walls.push_back(wall_ptr);
}

void GeoOctree::buildOctree() {
	std::cout << "Current node has " << m_walls.size() << " walls\n";

	if (!subdivide())
		return;

	// Check if each wall can fit into each node
	for (auto& wall : m_walls)
	{
		// Get AABB of the wall
		auto geometricHeight = MeshBuilder::getWallGeometricHeight(*wall);

		glm::vec3 min = glm::vec3(wall->startPosition.x - 0.01f, 
			((float)wall->floor + geometricHeight.bottom) * WORLD_HEIGHT, wall->startPosition.y - 0.01f);

		glm::vec3 max = glm::vec3(wall->endPosition.x + 0.01f, 
			((float)wall->floor + geometricHeight.top) * WORLD_HEIGHT, wall->endPosition.y + 0.01f);

		for (auto& node : m_nodes)
		{
			if (node->checkIfWallInsideAABB(*wall, min, max))
			{
				node->insertWall(wall);
			}
		}
	}

	// For debugging
	for (auto& node : m_nodes)
		std::cout << "Node: " << m_walls.size() << " - > " << node->getObjectSize() << "\n";

	// Recursive
	for (auto& node : m_nodes)
		node->buildOctree();

	//m_walls.clear();
}

void GeoOctree::cleanOctree() {

}

void GeoOctree::drawOctree(Renderer & renderer) const
{
	m_boundingBox->render(renderer);

	// Draw bounding boxes as wireframe
	if (subdivided)
		for (auto& node : m_nodes)
			node->drawOctree(renderer);
}

int GeoOctree::getObjectSize() const
{
	return m_walls.size();
}

std::vector<std::shared_ptr<Wall>> GeoOctree::getWallVectorNearPoint(const glm::vec3& point)
{
	if (!subdivided)
		return m_walls;

	for (auto& node : m_nodes)
		if (node->checkPointInOctree(point))
			return node->getWallVectorNearPoint(point);

	// fail safe (Caused by point outside of the octree)
	//std::cout << "Warning: Point is outside the octree\n";
	return std::vector<std::shared_ptr<Wall>>();
}

bool GeoOctree::checkPointInOctree(const glm::vec3 & point) const
{
	return m_boundingBox->checkAABB(point);
}

bool GeoOctree::checkIfTwoPointsInSameOctree(const glm::vec3 & p1, const glm::vec3 & p2) const
{
	// Base case
	if (!subdivided)
		return (m_boundingBox->checkAABB(p1) && m_boundingBox->checkAABB(p2));

	// Step Case (Find octree with point p1)
	for (auto& node : m_nodes)
		if (node->checkPointInOctree(p1))
			return node->checkIfTwoPointsInSameOctree(p1, p2);

	// fail safe
	return true;
}

/*bool GeoOctree::checkForCollision(const glm::vec3& start, const glm::vec3& end)
{
	return false;
}*/