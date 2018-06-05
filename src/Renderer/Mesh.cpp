#include "Mesh.h"

template <typename T>
void clear(std::vector<T>& v)
{
    v.clear();
    v.shrink_to_fit();
}

void Mesh::clearData()
{
    clear(verticies);
    clear(texCoords);
    clear(normals);
    clear(colour);
    clear(indices);
}
