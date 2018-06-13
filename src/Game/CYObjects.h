#pragma once

#include <string>
#include <cstdint>

#include "CYObjectProperties.h"

enum class ObjectID
{
    end,
    Wall,
    Platform
};

struct LevelHeader
{
    template <typename Archive>
    void archive(Archive& archive)
    {
        archive(gameAuthor, gameName, floorCount);
    }

    std::string gameName;
    std::string gameAuthor;
    u8 floorCount;
};

struct Wall
{
    template <typename Archive>
    void archive(Archive& archive)
    {
        archive(Wall, floor, 
            startPosition, endPosition, 
            frontMaterial, backMaterial, 
            Property::Type::Height, height);
    }

    Property::Position startPosition;
    Property::Position endPosition;
    Property::Material frontMaterial;
    Property::Material backMaterial;

    u8 floor;
    u8 height;
};

struct Platform
{
    template <typename Archive>
    void archive(Archive& archive)
    {
        archive(Platform, floor, position, material, Property::Type::Height, height);
    }

    Property::Position position; 
    Property::Material material;

    u8 floor;
    u8 height;
};

