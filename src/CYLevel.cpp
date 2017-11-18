#include "CYLevel.h"

void CYLevel::addWall(const std::smatch& match_groups)
{
    CYWall *wall = new CYWall(match_groups);
    m_editorObjects.push_back(wall);
}

void CYLevel::addPlat(const std::smatch& match_groups)
{
    CYPlat *plat = new CYPlat(match_groups);
    m_editorObjects.push_back(plat);
}


void CYLevel::destroyObjects()
{
    for (auto e_obj : m_editorObjects)
    {
        delete e_obj;
    }
}
