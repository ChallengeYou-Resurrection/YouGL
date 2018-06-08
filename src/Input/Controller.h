#pragma once

#include "../Maths/GlmCommon.h"

namespace sf { class RenderWindow; }

class Controller
{
    public:
        virtual bool forwardPressed() const = 0;
        virtual bool backPressed() const = 0;
        virtual bool leftPressed() const = 0;
        virtual bool rightPressed() const = 0;
        virtual bool jumpPressed() const = 0;
        virtual bool firePressed() const = 0;

        virtual glm::vec3 getLookChange() const = 0;
        virtual void tryToggleLookLock() = 0;

    protected:
        enum class Input
        {
            Forward,
            Back,
            Left,
            Right,
            Jump,
            Fire,
            MouseLock
        };
};
