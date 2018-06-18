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
    using Position = sf::Vector2<i16>;
    using Colour = sf::Color;

    struct Material
    {
        Colour colour;
        TextureID textureId;
    };
}


namespace cereal 
{
    //Serialisation/ Deserialisation functions

    //
    //Colour
    //
    template <typename Archive>
    void serialize(Archive& archive, Property::Colour& colour)
    {
        archive(colour.r, colour.g, colour.b);
    }

    //
    //Position
    //
    template <typename Archive>
    void serialize(Archive& archive, Property::Position& position)
    {
        archive(position.x, position.y);
    }

    //
    //Material 
    //
    template <typename Archive>
    void serialize(Archive& archive, Property::Material& material)
    {
        archive(material.colour, material.textureId);
    }
}