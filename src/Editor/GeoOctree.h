#ifndef GEOOCTREE_H
#define GEOOCTREE_H

#include <memory>
#include <vector>
#include <array>

#include <SFML/Graphics.hpp>
#include "glm/vec3.hpp"

//#include "EditorObject.h"
#include "BoundingBox.h"
#include "../Game/WorldConstants.h"
#include "../Game/CYObjects.h"
#include "../Game/MeshBuilder.h"

/* GEO OCTREE
 * This isn't an exact Octree but one designed to suit how the geometry in
 * CY works. This is because something like a wall may span through the entire
 * level thus either having to be split up or be in multiple.

 * Due to the nature of the editor, I can't really split up the walls without
 * having to recalculate the octree everytime there's a change. This ultimately means
 * that some walls will be tested multiple times. Hopefully a test will determine the
 * difference between it and a naive collision detection.
*/

const int MAX_ITEMS_PER_OCTREE = 128;
const int MAX_OCTREE_DEPTH     = 8;

class GeoOctree
{
    public:
        // Constructor, power of 2 recommended
        GeoOctree(int octreeSize);
		GeoOctree(int octreeSize, std::unique_ptr<BoundingBox> bb, const glm::vec3& origin);

        // Add geometry to octree
        //void insertGeometry(std::unique_ptr<EditorObject> obj);
		void insertWall(std::shared_ptr<Wall> wall_ptr);

        // Build Octree
        // To be called after all objects have been inserted
        void buildOctree();

        // Safely dispose of contents in Octree
        void cleanOctree();

		void drawOctree(Renderer& renderer) const;

		int getObjectSize() const;
		bool checkPointInOctree(const glm::vec3& point) const;
		bool checkIfTwoPointsInSameOctree(const glm::vec3& p1, const glm::vec3& p2) const;
		//bool checkForCollision(const glm::vec3& start, const glm::vec3& end);
		std::vector<std::shared_ptr<Wall>> getWallVectorNearPoint(const glm::vec3& point);

    protected:

    private:
        int size;
		glm::vec3 m_origin;

        //std::vector<std::shared_ptr<EditorObject>> m_objects;
		std::vector<std::shared_ptr<Wall>> m_walls;

		bool checkIfWallInsideAABB(const Wall& wall, const glm::vec3& min,
			const glm::vec3& max);

		bool subdivide();
        bool subdivided = false;
		std::unique_ptr<BoundingBox> m_boundingBox;
        std::vector<BoundingBox> m_subdivisionBB;
        std::array<std::unique_ptr<GeoOctree>, 8> m_nodes;
};

#endif // GEOOCTREE_H
