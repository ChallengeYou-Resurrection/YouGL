#pragma once

#include <string>
#include <cstdint>
#include <cereal/types/string.hpp>

#include "CYObjectProperties.h"


struct LevelHeader
{
    template <typename Archive>
    void serialize(Archive& archive)
    {
        archive(formatVersion, gameAuthor, gameName, floorCount);
    }

    u32 formatVersion;
    std::string gameName;
    std::string gameAuthor;
    u8 floorCount;
};

//
//  Wall
//
struct Wall
{
    template <typename Archive>
    void serialize(Archive& archive) 
    {
        archive(floor, startPosition, endPosition,
            frontMaterial, backMaterial, height);
    }

    Property::Position startPosition;
    Property::Position endPosition;
    Property::Material frontMaterial;
    Property::Material backMaterial;

    u8 floor;
    u8 height;
};


//
//  Platform
//
struct Platform
{
    template <typename Archive>
    void serialize(Archive& archive) 
    {
        archive(floor, position, material, height);
    }

    Property::Position position; 
    Property::Material material;

    u8 floor;
    u8 height;
};

