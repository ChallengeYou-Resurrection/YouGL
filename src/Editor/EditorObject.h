#ifndef EDITOROBJECT_H
#define EDITOROBJECT_H

#include <regex>

// For the JSON format CY Levels
#include <Utils/json.h>
using json = nlohmann::json;

class EditorObject
{
public:
    EditorObject();

    virtual void toJsonFormat(json& jLevel, int id) = 0;

    std::string type = "NONE";
private:
};

#endif // EDITOROBJECT_H
