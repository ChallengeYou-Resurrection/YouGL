#pragma once

#include "WorldTextures.h"
#include <SFML/Graphics.hpp>
#include "../Util/Types.h"

enum class PropertyType  : u8
{
    Position,
    Size,
    Material,
    Height,
    Direction
};

namespace Property
{
    enum class Type : u8
    {
        End,
        Position,
        Size,
        Material,
        Height,
        Direction
    };

    using Position = sf::Vector2<i16>;
    using Colour = sf::Color;

    struct Material
    {
        Colour colour;
        TextureID textureId;
    };
}

//Serialisation/ Deserialisation functions
template <typename Archive>
void archive(Archive& archive, Property::Position& position)
{
    archive(Property::Type::Position, position.x, position.y);
}

template <typename Archive>
void archive(Archive& archive, Property::Colour& colour)
{
    archive(Property::Type::Colour, colour.r, colour.g, colour.b);
}

template <typename Archive>
void archive(Archive& archive, Property::Material& material)
{
    archive(Property::Type::Material, material.colour, material.textureId);
}
