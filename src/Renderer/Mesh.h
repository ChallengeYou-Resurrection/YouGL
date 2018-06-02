#pragma once

#include <vector>
#include <glad.h>

struct Mesh
{
    std::vector<GLfloat> verticies;
    std::vector<GLfloat> texCoords;
    std::vector<GLfloat> normals;
    std::vector<GLuint> indices;

    void clearData();
};