#ifndef GEOOCTREE_H
#define GEOOCTREE_H

#include <memory>
#include <vector>
#include <array>

#include <SFML/Graphics.hpp>
#include "glm/vec3.hpp"

//#include "EditorObject.h"
#include "BoundingBox.h"

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

class GeoOctree
{
    public:
        // Constructor, power of 2 recommended
        GeoOctree(int octreeSize);

        // Add geometry to octree
        //void insertGeometry(std::unique_ptr<EditorObject> obj);

        // Build Octree
        // To be called after all objects have been inserted
        void buildOctree();

        // Safely dispose of contents in Octree
        void cleanOctree();

		void drawOctree(Renderer& renderer);

    protected:

    private:
        int size;

        //std::vector<std::shared_ptr<EditorObject>> m_objects;

        bool subdivided = false;
        std::vector<BoundingBox> m_subdivisionBB;
        std::array<std::unique_ptr<GeoOctree>, 8> m_nodes;
};

#endif // GEOOCTREE_H
