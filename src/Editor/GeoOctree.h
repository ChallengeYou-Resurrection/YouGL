#ifndef GEOOCTREE_H
#define GEOOCTREE_H

#include <memory>
#include <vector>
#include <array>

#include <SFML/Graphics.hpp>
#include "glm/vec3.hpp"

#include "EditorObject.h"

/* GEO OCTREE
 * This isn't an exact Octree but one designed to suit how the geometry in
 * CY works. This is because something like a wall may span through the entire
 * level thus either having to be split up or be in multiple.

 * Due to the nature of the editor, I can't really split up the walls without
 * having to recalculate the octree everytime there's a change. This ultimately means
 * that some walls will be tested multiple times. Hopefully a test will determine the
 * difference between it and a naive collision detection.
*/

const int MAX_ITEMS_PER_OCTREE = 12;
const int MAX_OCTREE_DEPTH     = 8;

class GeoOctree;

// For AABB collision
// Used for determining what subdivision an object should go to
struct BoundingBox {
    glm::vec3 m_vecMin;
    glm::vec3 m_vecMax;

    bool checkAABB(const BoundingBox& obj)
    {
        return (this->m_vecMax.x > obj.m_vecMin.x &&
                this->m_vecMin.x < obj.m_vecMax.x &&
                this->m_vecMax.y > obj.m_vecMin.y &&
                this->m_vecMin.y < obj.m_vecMax.y &&
                this->m_vecMax.z > obj.m_vecMin.z &&
                this->m_vecMin.z < obj.m_vecMax.z);
    }
};

class GeoOctree
{
    public:
        // Constructor, power of 2 recommended
        GeoOctree(int octreeSize);

        // Add geometry to octree
        void insertGeometry(std::unique_ptr<EditorObject> obj);

        // Build Octree
        // To be called after all objects have been inserted
        void buildOctree();

        // Safely dispose of contents in Octree
        void cleanOctree();

    protected:

    private:
        std::vector<std::shared_ptr<EditorObject>> m_objects;

        bool subdivided = false;
        std::array<BoundingBox, 8> m_subdivisionBB;
        std::array<std::unique_ptr<GeoOctree>, 8> m_nodes;
};

#endif // GEOOCTREE_H
