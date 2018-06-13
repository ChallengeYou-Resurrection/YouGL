#include "OldFormatUtil.h"

#include <regex>
#include <iostream>

namespace
{
    const Property::Colour WHITE = { 255, 255, 255 };

    Property::Colour stringToColour(const std::string& colourString)
    {
        size_t valueEnd;
        int pointer = 7;
        auto getComponent = [&](sf::Uint8& comp)
        {
            valueEnd = colourString.find(",", pointer);
            comp = (sf::Uint8)std::stoi(colourString.substr(pointer, valueEnd - pointer));
            pointer = valueEnd + 2;
        };

        Property::Colour colour;
        getComponent(colour.r);
        getComponent(colour.g);
        getComponent(colour.b);
        return colour;
    }

    Property::Position extractVector(const std::smatch& match, int firstIndex)
    {
        Property::Position vector;
        //Extract x
        vector.x = (u16)std::stoi(match[firstIndex]);

        //Extract y
        vector.y = (u16)std::stoi(match[firstIndex + 1]);

        return vector;
    }

    Property::Material extractMaterial(const std::smatch& match, int firstIndex)
    {
        Property::Material material;

        if (match[firstIndex] != "") { //Colour
            material.colour = stringToColour(match[firstIndex].str());
        }
        else {  //Texture
            material.textureId = (u8)std::stoi(match[firstIndex + 1].str());
            material.colour = WHITE;
        }
        return material;
    }
}

namespace OldFormat
{
    LevelHeader extractHeader(std::string& levelData)
    {
        LevelHeader header;
        std::smatch matchGroups;
        std::regex headerRegex("#name: \"([^\"]+)\", #levels: (\\d+), #version: ([^,]+), #creator: \"([^\"]+)\"");

        if (std::regex_search(levelData, matchGroups, headerRegex)) {
            header.gameName = matchGroups[1].str();
            header.floorCount = (u8)std::stoi(matchGroups[2].str());
            header.gameAuthor = matchGroups[4].str();
        }
        else {
            std::cout << "Cannot match header\n";
            return {};
        }
        return header;
    }

    std::vector<Wall> extractWalls(std::string& wallData)
    {
        std::vector<Wall> walls;
        std::smatch matchGroups;
        std::regex wallRegex("\\[(-?\\d+), (-?\\d+), (-?\\d+), (-?\\d+), \\[(c[^\\)]*\\))?(\\d+)?, (c[^\\)]*\\))?(\\d+)?\\]?, (\\d+)\\],? ?(\\d+)?");
        while (std::regex_search(wallData, matchGroups, wallRegex))
        {
            Wall wall;
            //Wall position
            auto displacement = extractVector(matchGroups, 1);
            wall.startPosition = extractVector(matchGroups, 3);
            wall.endPosition = { displacement.x + wall.startPosition.x,
                displacement.y + wall.startPosition.y };

            //Texture
            wall.frontMaterial = extractMaterial(matchGroups, 5);
            wall.backMaterial = extractMaterial(matchGroups, 7);

            //Height and floor
            if (matchGroups[10] != "") {
                wall.height = (u8)std::stoi(matchGroups[9].str());
                wall.floor  = (u8)std::stoi(matchGroups[10].str());
            }
            else {//Old versions have no wall height
                wall.height = 1;
                wall.floor = (u8)std::stoi(matchGroups[9].str());
            }
            walls.push_back(wall);
            wallData = matchGroups.suffix();


        }
        return walls;
    }
}