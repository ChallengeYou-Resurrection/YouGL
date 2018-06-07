#pragma once

#include <vector>
#include <glad.h>

struct Mesh
{
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> texCoords;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> colour;
    std::vector<GLuint> indices;

    void clearData();
};
