#ifndef CYWALL_H
#define CYWALL_H

#include <iostream>
#include <regex>
#include <SFML/Graphics.hpp>

#include "EditorObject.h"

class CYWall : public EditorObject
{
public:
    // Construct from Regex
    CYWall(const std::smatch& matchGroups);
	CYWall(const json& jObj);

    virtual void toJsonFormat(json& jLevel, int id);

    virtual void createModel();
    virtual void render(Renderer& renderer);

private:
    sf::Vector2f m_startPosition = sf::Vector2f(0, 0);
    sf::Vector2f m_displacementPosition = sf::Vector2f(0, 0);

	Material m_frontMaterial;
    Material m_backMaterial;

    float m_startHeight;
	float m_endHeight;
    int m_level;
};

#endif // CYWALL_H
