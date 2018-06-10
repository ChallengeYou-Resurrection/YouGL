#ifndef EDITOROBJECT_H
#define EDITOROBJECT_H

#include "../Renderer/Model.h"
#include "../Renderer/Mesh.h"
#include "../Renderer/Renderer.h"

#include <regex>
#include <array>
#include <string>

// For the JSON format CY Levels
#include <json.hpp>
using json = nlohmann::json;

const float WORLD_WIDTH_SCALE  = 1.0f;
const float WORLD_HEIGHT_SCALE = 1.2f;

struct Material {
	int textureId;
	std::array<GLfloat, 3> colour;

	// For converting decimal colour values into integers
	// Used for serializing 
	std::array<int, 3> serializeColour()
	{
		std::array<int, 3> int_colour;
		for (int i = 0; i < 3; i++)
			int_colour[i] = colour[i] * 255;

		return int_colour;
	}

	void deserializeColour(std::array<int, 3> int_colour)
	{
		for (int i = 0; i < 3; i++)
			colour[i] = int_colour[i] / 255.f;
	}
};

class EditorObject
{
public:
    EditorObject();
	static std::array<GLfloat, 3> stringToColor(const std::string& color);

    virtual void toJsonFormat(json& jLevel, int id) = 0;

    virtual void createModel() = 0;
    virtual void render(Renderer& renderer) = 0;

    std::string type = "NONE";

protected:
    Model m_geometry;

private:

};

#endif // EDITOROBJECT_H
