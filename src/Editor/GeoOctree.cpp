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
	if (m_objects.size() < MAX_ITEMS_PER_OCTREE)
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

bool GeoOctree::checkIfObjectInsideAABB(const std::shared_ptr<CYGeneric> obj, 
	const glm::vec3& min, const glm::vec3& max) const
{
	return m_boundingBox->checkAABB(min, max);
}

void GeoOctree::insertGeometry(std::shared_ptr<CYGeneric> obj_ptr)
{
	m_objects.push_back(obj_ptr);
}

void GeoOctree::buildOctree() {
	//std::cout << "Current node has " << m_walls.size() << " walls\n";

	if (!subdivide())
		return;

	// Check if each wall can fit into each node
	for (auto& obj : m_objects)
	{
		// Get AABB of the object
		auto objAABB = obj->getAABB();

		/*auto geometricHeight = MeshBuilder::getWallGeometricHeight(*wall);

		glm::vec3 min = glm::vec3(wall->startPosition.x - 0.01f, 
			((float)wall->floor + geometricHeight.bottom) * WORLD_HEIGHT, wall->startPosition.y - 0.01f);

		glm::vec3 max = glm::vec3(wall->endPosition.x + 0.01f, 
			((float)wall->floor + geometricHeight.top) * WORLD_HEIGHT, wall->endPosition.y + 0.01f);
			*/

		for (auto& node : m_nodes)
		{
			if (node->checkIfObjectInsideAABB(obj, objAABB.m_vecMin, objAABB.m_vecMax))
			{
				node->insertGeometry(obj);
			}
		}
	}

	// For debugging
	//for (auto& node : m_nodes)
		//std::cout << "Node: " << m_walls.size() << " - > " << node->getObjectSize() << "\n";

	// Recursive
	for (auto& node : m_nodes)
		node->buildOctree();

	m_objects.clear();
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
	return m_objects.size();
}

int GeoOctree::getTotalObjectSize() const
{
	if (subdivided)
	{
		// Step case
		int objCount = 0;
		for (auto& node : m_nodes)
			objCount += node->getTotalObjectSize();
		return objCount;
	}
	else {
		// Base case
		return this->getObjectSize();
	}
}

std::vector<std::shared_ptr<Wall>> GeoOctree::getWallVectorNearPoint(const glm::vec3& point)
{
	/*if (!subdivided)
		return m_walls;

	for (auto& node : m_nodes)
		if (node->checkPointInOctree(point))
			return node->getWallVectorNearPoint(point);

	// fail safe (Caused by point outside of the octree)
	//std::cout << "Warning: Point is outside the octree\n";
	return std::vector<std::shared_ptr<Wall>>();*/
	return {};
}

bool GeoOctree::checkIfRayIntersectsOctree(const MouseRay::Ray & mRay)
{
	std::optional<float> d = this->m_boundingBox->checkRayCast(mRay, 0.f, 50.f);
	return (d.has_value() ? true : false);
}

// Note, this returns a negative number if there's no intersection
float GeoOctree::rayDistanceToNode(const MouseRay::Ray& mRay)
{
	std::optional<float> d = this->m_boundingBox->checkRayCast(mRay, 0.f, 50.f);
	return d.value_or(-1.f);
}

bool GeoOctree::checkPointInOctree(const glm::vec3 & point) const
{
	return m_boundingBox->checkPoint(point);
}

bool GeoOctree::checkPointNearOctree(const glm::vec3 & point, float margin) const
{
	return m_boundingBox->checkIfPointNear(point, margin);
}

bool GeoOctree::checkIfTwoPointsInSameOctree(const glm::vec3 & p1, const glm::vec3 & p2) const
{
	// Base case
	if (!subdivided)
		return (m_boundingBox->checkPoint(p1) && m_boundingBox->checkPoint(p2));

	// Step Case (Find octree with point p1)
	for (auto& node : m_nodes)
		if (node->checkPointInOctree(p1))
			return node->checkIfTwoPointsInSameOctree(p1, p2);

	// fail safe
	return true;
}

int GeoOctree::nodesIntersectingRay(const MouseRay::Ray& mRay)
{
	// If there's not intersection, then ignore
	if (!checkIfRayIntersectsOctree(mRay))
		return 0;

	if (subdivided)
	{
		// Step case
		// If it's a parent node, add up the results of the nodes
		int nodeCount = 0;
		for (auto& node : m_nodes)
			nodeCount += node->nodesIntersectingRay(mRay); 

		return nodeCount;
	}
	else {
		// If child node, then represent it as 1
		return 1;
	}
}

std::vector<GeoOctree::NodeDistance> 
GeoOctree::getNodesIntersectingRayOrdered(const MouseRay::Ray& mRay)
{
	// Error check
	if (!checkIfRayIntersectsOctree(mRay) )
		return {};

	// Generate a vector containing all nodes intersecting with ray along with distance to each node
	std::vector<GeoOctree::NodeDistance> unorderedNodes;
	this->getNodesIntersectingRay(mRay, unorderedNodes);

	// Sort them
	std::sort(unorderedNodes.begin(), unorderedNodes.end());

	return std::move(unorderedNodes);
}

void GeoOctree::getNodesIntersectingRay(const MouseRay::Ray& mRay, std::vector<GeoOctree::NodeDistance>& nodes)
{
	// Get distance & return if it's -1
	float dist = rayDistanceToNode(mRay);
	if (dist < 0)
		return;

	if (subdivided) {
		for (auto& node : m_nodes)
			node->getNodesIntersectingRay(mRay, nodes);
	}
	else {
		nodes.push_back(std::make_pair(dist, this));
	}

	return;
}

std::optional<std::shared_ptr<CYGeneric>> GeoOctree::getObjectClosestToRay(const MouseRay::Ray & mRay)
{
	// If it's subdivided then it will not have any objects
	if (subdivided)
		return std::nullopt;

	float distToClosestObject = INFINITE;
	std::shared_ptr<CYGeneric> closestObject;
	for (auto& obj : m_objects)
	{
		// Get the collision mesh of the object & check it's not empty
		const auto& c_mesh = obj->getCollisionMesh();
		if (c_mesh.size() > 0)
		{
			for (auto& c_poly : c_mesh)
			{
				glm::vec3 b_pos;

				// Use built-in GLM's Ray vs Triangle detection
				if (glm::intersectRayTriangle(mRay.origin, mRay.direction, c_poly.vertex[0],
					c_poly.vertex[1], c_poly.vertex[2], b_pos))
				{
					// Get point of intersection, b_pos.z is the distance from the origin of the ray
					//glm::vec3 c_pos = glm::vec3(3,3,3);

					if (b_pos.z < distToClosestObject)
					{
						// Due to the nature of the octree, there needs to be a check
						// that the point of intersection is inside the node or else it may 
						// ignore closer items in a later octree (due to overlapping elements)
						glm::vec3 poi = (mRay.origin + mRay.direction * b_pos.z) * WORLD_SIZE;

						if (this->checkPointNearOctree(poi, 0.1f))
						{
							distToClosestObject = b_pos.z;
							closestObject = obj;
						}
					}
				}
			}
		}
	}

	// Return the closest object found
	if (closestObject != nullptr)
		return closestObject;

	return std::nullopt;
}

/*bool GeoOctree::checkForCollision(const glm::vec3& start, const glm::vec3& end)
{
	return false;
}*/