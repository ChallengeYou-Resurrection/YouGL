#include "CYWall.h"


CYWall::CYWall(const std::smatch& match_groups)
{
    std::ssub_match sub_match;

    sub_match = match_groups[1];
    std::cout << "Start_X: " << sub_match.str() << std::endl;

    sub_match = match_groups[2];
    std::cout << "Start_Y: " << sub_match.str() << std::endl;

    sub_match = match_groups[3];
    std::cout << "Displacement_X: " << sub_match.str() << std::endl;

    sub_match = match_groups[4];
    std::cout << "Displacement_Y: " << sub_match.str() << std::endl;

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
    std::cout << "Texture 2: " << sub_match.str() << std::endl;

    // If 10 doesn't exist then 9 = Level, else 9 = Z_Index
    if (match_groups[10] != "") {
        sub_match = match_groups[9];
        std::cout << "Z_Index: " << sub_match.str() << std::endl;

        sub_match = match_groups[10];
        std::cout << "Level: " << sub_match.str() << std::endl;
    } else {
        sub_match = match_groups[9];
        std::cout << "Level: " << sub_match.str() << std::endl;
    }
}
