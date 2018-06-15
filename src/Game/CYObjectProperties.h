#pragma once

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
        u8 textureId;
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
    void save(Archive& archive, const Property::Position& position)
    {
        archive(Property::Type::Position, position.x, position.y);
    }

    template <typename Archive>
    void load(Archive& archive, Property::Position& position)
    {
        archive(position.x, position.y);
    }


    //
    //Material 
    //
    template <typename Archive>
    void save(Archive& archive, const Property::Material& material)
    {
        archive(Property::Type::Material, material.colour, material.textureId);
    }

    template <typename Archive>
    void load(Archive& archive, Property::Material& material)
    {
        archive(material.colour, material.textureId);
    }
}