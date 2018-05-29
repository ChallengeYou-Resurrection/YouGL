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

    /*
    // Start
    file << "{\n";

    // Headers
    file << "\"name\": \"" << m_header.name << "\",\n";
    file << "\"author\": \"" << m_header.author << "\",\n";
    file << "\"version\": " << m_header.version << ",\n";
    file << "\"levels\": " << m_header.levels << ",\n";

    // Walls
    file << "\"walls\": {\n";
    for (auto obj : this->m_editorObjects)
    {
        if ( obj->type == "WALL")
        {
            // If not the first object add a comma
            if (id != 0)
                file << ",\n";

            file << "\"" << id << "\" : " << obj->toJsonFormat();
            id++;
        }

    }
    file << "\n}\n";

    // End
    file << "}\n";
    file.close();
    */

    return true;
}

void CYLevel::destroyObjects()
{
    for (auto e_obj : m_editorObjects)
    {
        delete e_obj;
    }
}
