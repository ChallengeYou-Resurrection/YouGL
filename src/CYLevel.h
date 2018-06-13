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
    void addEditorObjectFromRegex(const std::smatch& matchGroups);

    // Serialize
    bool serializeIntoOldFormat();
    bool serializeIntoJsonFormat(std::string file_name);
    bool serialize();

    // TODO: Create a static level
    bool compileMap();

    // Editor Objects
    void addWall(const std::smatch& matchGroups);
    void addPlat(const std::smatch& matchGroups);

	// JSON : Editor Objects
	void addWall(const json& jObj);
	void addPlat(const json& jObj);

	void drawOctree(Renderer& renderer);
    void drawGeometry(Renderer& renderer);
    void buildGeometry();

    // Clean up
    void destroyObjects();

private:
    std::vector<std::shared_ptr<EditorObject>> m_editorObjects;

    GeoOctree m_octree;
};

#endif // CYLEVEL_H
