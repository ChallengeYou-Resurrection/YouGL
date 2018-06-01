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

bool CYLevel::serializeIntoJsonFormat(std::string file_name)
{
    int id = 0;

    json jLevel;

    // Level Headers
    jLevel["NAME"] = m_header.name;
    jLevel["AUTHOR"] = m_header.author;
    jLevel["VERSION"] = m_header.version;
    jLevel["LEVELS"] = m_header.levels;

    // WALLS
    for (auto obj : this->m_editorObjects)
    {
        if ( obj->type == "WALL")
        {
            obj->toJsonFormat(jLevel, id);
            id++;
        }

    }

    // Write to file
    std::ofstream file(file_name);
    file << jLevel.dump();
    file.close();

    return true;
}

void CYLevel::destroyObjects()
{
    for (auto e_obj : m_editorObjects)
    {
        delete e_obj;
    }
}
