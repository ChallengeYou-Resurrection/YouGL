#ifndef CYLEVEL_H
#define CYLEVEL_H

#include <string>
#include <regex>

#include "CYWall.h"

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
    bool serialize();

    bool compileMap();

    // Editor Objects
    void addWall(const std::smatch& match_groups);

    // Clean up
    void destroyObjects();

private:
    std::vector<EditorObject*> m_editorObjects;
};

#endif // CYLEVEL_H
