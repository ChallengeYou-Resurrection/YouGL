#ifndef CYPLAT_H
#define CYPLAT_H

#include <iostream>
#include <regex>
#include <SFML/Graphics.hpp>

#include "EditorObject.h"

class CYPlat : public EditorObject
{
public:
    // Construct from Regex
    CYPlat(const std::smatch& matchGroups);
	CYPlat(const json& jObj);

    virtual void toJsonFormat(json& jLevel, int id);

    virtual void createModel();
    virtual void render(Renderer& renderer);

    std::string type = "PLAT";

protected:
    sf::Vector2f m_position;
    sf::Vector2f m_size;

    int m_texture;

    int m_height;
    int m_level;

private:
};

#endif // CYPLAT_H
