#include "MeshBuilder.h"

#include <array>
#include <iostream>
#include <iomanip>

#include "../Maths/GlmCommon.h"
#include "CYObjects.h"
#include "WorldConstants.h"

namespace {
    struct WallHeight 
    {
        float bottom;
        float top;
    };

    WallHeight getWallGeometricHeight(const Wall& wall) 
    {
        float bottomHeight = 0.0f;
        float topHeight = 1.0f;

        switch (wall.height) {
            case 2:  topHeight = 3 / 4.0f;  bottomHeight = 0.0f; break;
            case 3:  topHeight = 2 / 4.0f;  bottomHeight = 0.0f; break;
            case 4:  topHeight = 1 / 4.0f;  bottomHeight = 0.0f; break;

            case 5:  topHeight = 2 / 4.0f;  bottomHeight = 1 / 4.0f; break;
            case 6:  topHeight = 3 / 4.0f;  bottomHeight = 2 / 4.0f; break;
            case 7:  topHeight = 4 / 4.0f;  bottomHeight = 3 / 4.0f; break;

            case 8:  topHeight = 4 / 4.0f;  bottomHeight = 2 / 4.0f; break;
            case 9:  topHeight = 4 / 4.0f;  bottomHeight = 1 / 4.0f; break;
            case 10: topHeight = 3 / 4.0f;  bottomHeight = 1 / 4.0f; break;
            default: topHeight = 4 / 4.0f;  bottomHeight =     0.0f; break;
        }
        return { 
            bottomHeight, topHeight 
        };
    }
}

/////////////
///  WALL  //
/////////////
Mesh createMesh(const Wall& wall)
{
    Mesh mesh;
    auto geometricHeight = getWallGeometricHeight(wall);

    //Do some geometric calculations (maths done by Ruixel)
    float minHeight = ((float)wall.floor + geometricHeight.bottom) / WORLD_HEIGHT;
    float maxHeight = ((float)wall.floor + geometricHeight.top)    / WORLD_HEIGHT;

    glm::vec2 wallOrigin = { (float)wall.startPosition.x, (float)wall.startPosition.y };
    glm::vec2 wallFinish = { (float)wall.endPosition.x, (float)wall.endPosition.y };

    std::array<glm::vec3, 4> vertices;
    vertices[0] = glm::vec3((wallOrigin.x) / WORLD_SIZE, maxHeight, (wallOrigin.y) / WORLD_SIZE);
    vertices[1] = glm::vec3((wallFinish.x) / WORLD_SIZE, maxHeight, (wallFinish.y) / WORLD_SIZE);
    vertices[2] = glm::vec3((wallFinish.x) / WORLD_SIZE, minHeight, (wallFinish.y) / WORLD_SIZE);
    vertices[3] = glm::vec3((wallOrigin.x) / WORLD_SIZE, minHeight, (wallOrigin.y) / WORLD_SIZE);
    

    glm::vec3 normal = glm::cross(vertices[2] - vertices[1], vertices[3] - vertices[1]);

    //Vertices
    mesh.vertices.insert(mesh.vertices.end(), { vertices[1].x, vertices[1].y, vertices[1].z });
    mesh.vertices.insert(mesh.vertices.end(), { vertices[2].x, vertices[2].y, vertices[2].z });
    mesh.vertices.insert(mesh.vertices.end(), { vertices[3].x, vertices[3].y, vertices[3].z });
    mesh.vertices.insert(mesh.vertices.end(), { vertices[0].x, vertices[0].y, vertices[0].z });

    //Normals
    for (int i = 0; i < 4; i++) {
        mesh.normals.insert(mesh.normals.end(), { normal.x, normal.y, normal.z });
    }

    //Colours
    for (int i = 0; i < 4; i++) {
        mesh.colour.insert(mesh.colour.end(), {
            (float)wall.frontMaterial.colour.r / 255.0f,
            (float)wall.frontMaterial.colour.g / 255.0f,
            (float)wall.frontMaterial.colour.b / 255.0f
            });
    }

    //Textre Coords (To do)
    mesh.texCoords = {
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };

    mesh.indices = { 
        0, 3, 1, 1, 2, 3 
    };

    /*static int wn = 0;
    std::cout << "WALL " << wn++ << std::endl;
    std::cout << wall.startPosition.x << " " << wall.floor << " " << wall.startPosition.y << "\n";
    std::cout << wall.endPosition.x << " " << wall.floor << " " << wall.endPosition.y << "\n";
    int i = 0;
    for (auto& v : vertices) {
        std::cout 
            << " X: " << std::setw(3) << v.x 
            << " Y: " << std::setw(3) << v.y 
            << " Z: " << std::setw(3) << v.z << "\n";
    }
    std::cout << "\n"; */
    return mesh;
}