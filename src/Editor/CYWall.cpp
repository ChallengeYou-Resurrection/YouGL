#include "CYWall.h"

CYWall::CYWall(const std::smatch& match_groups)
{
    std::ssub_match sub_match;

    // Start Position
    sub_match = match_groups[1];
    this->m_start_pos = sf::Vector2f(std::stof(sub_match.str()), 0);
    sub_match = match_groups[2];
    this->m_start_pos.y = std::stof(sub_match.str());

    // Displacement Position
    sub_match = match_groups[3];
    this->m_displacement_pos = sf::Vector2f(std::stof(sub_match.str()), 0);
    sub_match = match_groups[4];
    this->m_displacement_pos.y = std::stof(sub_match.str());

    // 5 = Colour, 6 = TextureID
    if (match_groups[5] != "")
        sub_match = match_groups[5];
    else
        sub_match = match_groups[6];
    std::cout << "Texture: " << sub_match.str() << std::endl;

    // 7 = Colour, 8 = TextureID
    if (match_groups[7] != "")
        sub_match = match_groups[7];
    else
        sub_match = match_groups[8];
    //std::cout << "Texture 2: " << sub_match.str() << std::endl;

    // If 10 doesn't exist then 9 = Level, else 9 = Z_Index
    if (match_groups[10] != "") {
        sub_match = match_groups[9];    // Z_Index
        sub_match = match_groups[10];   // Level
    } else {
        sub_match = match_groups[9];    // Level
    }

    this->type = "WALL";
}



void CYWall::toJsonFormat(json& jLevel, int id)
{
    // Add in the properties to JSON
    jLevel["WALL"]["START_POS"]["x"] = m_start_pos.x;
    jLevel["WALL"]["START_POS"]["y"] = this->m_start_pos.y;

    jLevel["WALL"]["DISP_POS"]["x"] = this->m_displacement_pos.x;
    jLevel["WALL"]["DISP_POS"]["y"] = this->m_displacement_pos.y;

    jLevel["WALL"]["LEVEL"] = this->m_level;

    return;
}
