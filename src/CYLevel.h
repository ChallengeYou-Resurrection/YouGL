#ifndef CYLEVEL_H
#define CYLEVEL_H

#include <string>
#include <regex>
#include <fstream>

// For the JSON format CY Levels
#include <Utils/json.h>
using json = nlohmann::json;

#include "CYWall.h"
#include "CYPlat.h"

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

    // Clean up
    void destroyObjects();

private:
    std::vector<EditorObject*> m_editorObjects;
};

#endif // CYLEVEL_H
