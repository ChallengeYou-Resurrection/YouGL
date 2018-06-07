#ifndef CYLEVEL_H
#define CYLEVEL_H

#include <string>
#include <regex>
#include <memory>
#include <fstream>

// For the JSON format CY Levels
#include <json.hpp>
using json = nlohmann::json;

#include "Editor/CYWall.h"
#include "Editor/CYPlat.h"
#include "Editor/GeoOctree.h"

struct CYLevelHeader
{
    std::string name;
    std::string author;
    std::string date;

    float version;
    int levels;
};

class CYLevel
{
public:
    CYLevel();

    CYLevelHeader m_header;

    // Editor
    template<typename T>
    void addEditorObjectFromRegex(const std::smatch& match_groups);

    // Serialize
    bool serializeIntoOldFormat();
    bool serializeIntoJsonFormat(std::string file_name);
    bool serialize();

    // TODO: Create a static level
    bool compileMap();

    // Editor Objects
    void addWall(const std::smatch& match_groups);
    void addPlat(const std::smatch& match_groups);

    void drawGeometry(Renderer& renderer);

    // Clean up
    void destroyObjects();

private:
    std::vector<std::shared_ptr<EditorObject>> m_editorObjects;

    GeoOctree m_octree;
};

#endif // CYLEVEL_H
