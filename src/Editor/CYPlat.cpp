#include "CYPlat.h"

CYPlat::CYPlat(const std::smatch& match_groups)
{
    std::ssub_match sub_match;

    sub_match = match_groups[1];
    std::cout << "X: " << sub_match.str() << std::endl;

    sub_match = match_groups[2];
    std::cout << "Y: " << sub_match.str() << std::endl;

    // If group 4 and 5 are empty then it's
    // [X, Y, [Size], Level]
    if (match_groups[4] == "" && match_groups[5] == "") {
        sub_match = match_groups[3];
        std::cout << "Texture: " << sub_match.str() << std::endl;
    } else {
        // Else, 4/5 are texture and if 6 exists, it's the Z_Index
        sub_match = match_groups[3];
        std::cout << "Size: " << sub_match.str() << std::endl;

        // 4 = Colour, 5 = TextureID
        if (match_groups[4] != "")
            sub_match = match_groups[4];
        else
            sub_match = match_groups[5];
        std::cout << "Texture: " << sub_match.str() << std::endl;

        if (match_groups[6] != "") {
            sub_match = match_groups[6];
            std::cout << "Z_Index: " << sub_match.str() << std::endl;
        }
    }

    sub_match = match_groups[7];
    std::cout << "Level: " << sub_match.str() << std::endl;
}
