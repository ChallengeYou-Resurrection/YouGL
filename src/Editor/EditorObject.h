#ifndef EDITOROBJECT_H
#define EDITOROBJECT_H

#include <regex>

// For the JSON format CY Levels
#include <json.hpp>
using json = nlohmann::json;

class EditorObject
{
public:
    EditorObject();

    virtual void toJsonFormat(json& jLevel, int id) = 0;
    //virtual void createMesh();

    std::string type = "NONE";
private:
};

#endif // EDITOROBJECT_H
