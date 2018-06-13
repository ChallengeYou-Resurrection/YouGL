#include "Mesh.h"

template <typename T>
void clear(std::vector<T>& v)
{
    v.clear();
    v.shrink_to_fit();
}

void Mesh::clearData()
{
    clear(vertices);
    clear(texCoords);
    clear(normals);
    clear(colour);
    clear(indices);
}

void Mesh::combineWith(const Mesh & otherMesh)
{
    auto combine = [&](std::vector<GLfloat>& v1, const std::vector<GLfloat>& v2) {
        v1.insert(v1.end(), v2.begin(), v2.end());
    };
    combine(vertices,   otherMesh.vertices);
    combine(texCoords,  otherMesh.texCoords);
    combine(normals,    otherMesh.normals);
    combine(colour,     otherMesh.colour); 

	int i_size = (vertices.size() - 12) / 3;
    for (auto i : otherMesh.indices) {
        indices.push_back(i + i_size );
    }
}
