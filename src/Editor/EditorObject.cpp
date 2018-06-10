#include "EditorObject.h"

EditorObject::EditorObject()
{
    //ctor
}

std::array<GLfloat, 3> EditorObject::stringToColor(const std::string& color) 
{
	int ptr = 7;
	std::array<GLfloat, 3> colors; 

	size_t value_end = color.find(',', ptr);
	colors[0] = std::stof(color.substr(ptr, value_end - ptr)) / 255.f;
	ptr = value_end + 2;

	value_end = color.find(',', ptr);
	colors[1] = std::stof(color.substr(ptr, value_end - ptr)) / 255.f;
	ptr = value_end + 2;

	value_end = color.find(')', ptr);
	colors[2] = std::stof(color.substr(ptr, value_end - ptr)) / 255.f;

	return colors;
}