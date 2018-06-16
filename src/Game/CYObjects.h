#pragma once

#include <string>
#include <cstdint>
#include <cereal/types/string.hpp>

#include "CYObjectProperties.h"

enum class ObjectID : u8
{
    end,
    Wall,
    Platform
};

struct LevelHeader
{
    template <typename Archive>
    void serialize(Archive& archive)
    {
        archive(gameAuthor, gameName, floorCount);
    }

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
    void save(Archive& archive) const
    {
        archive(ObjectID::Wall, floor, startPosition, endPosition,
            frontMaterial, backMaterial, Property::Type::Height, height);
    }

    template <typename Archive>
    void load(Archive& archive)
    {
        archive(floor, startPosition, endPosition, frontMaterial, 
            backMaterial, Property::Type::Height, height);
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
    void save(Archive& archive) const
    {
        archive(ObjectID::Platform, floor, position, material, Property::Type::Height, height);
    }

    template <typename Archive>
    void load(Archive& archive)
    {
        archive(floor, position, material, Property::Type::Height, height);
    }

    Property::Position position; 
    Property::Material material;

    u8 floor;
    u8 height;
};

