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
    CYWall(const std::smatch& match_groups);

    virtual void toJsonFormat(json& jLevel, int id);

private:
    sf::Vector2f m_start_pos = sf::Vector2f(0, 0);
    sf::Vector2f m_displacement_pos = sf::Vector2f(0, 0);

    int m_texture1;
    int m_texture2;

    int m_start_height;
    int m_end_height;
    int m_level;
};

#endif // CYWALL_H
