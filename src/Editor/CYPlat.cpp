#include "CYPlat.h"

CYPlat::CYPlat(const std::smatch& matchGroups)
{
    std::ssub_match subMatch;

    subMatch = matchGroups[1];
    //std::cout << "X: " << subMatch.str() << std::endl;

    subMatch = matchGroups[2];
    //std::cout << "Y: " << subMatch.str() << std::endl;

    // If group 4 and 5 are empty then it's
    // [X, Y, [Size], Level]
    if (matchGroups[4] == "" && matchGroups[5] == "") {
        subMatch = matchGroups[3];
        //std::cout << "Texture: " << subMatch.str() << std::endl;
    } else {
        // Else, 4/5 are texture and if 6 exists, it's the Z_Index
        subMatch = matchGroups[3];
        //std::cout << "Size: " << subMatch.str() << std::endl;

        // 4 = Colour, 5 = TextureID
        if (matchGroups[4] != "")
            subMatch = matchGroups[4];
        else
            subMatch = matchGroups[5];
        //std::cout << "Texture: " << subMatch.str() << std::endl;

        if (matchGroups[6] != "") {
            subMatch = matchGroups[6];
            //std::cout << "Z_Index: " << subMatch.str() << std::endl;
        }
    }

    subMatch = matchGroups[7];
    //std::cout << "Level: " << subMatch.str() << std::endl;
}

CYPlat::CYPlat(const json & jObj)
{

}

void CYPlat::createModel() {
}

void CYPlat::render(Renderer& renderer)
{

}

void CYPlat::toJsonFormat(json& jLevel, int id)
{
    return;
}
