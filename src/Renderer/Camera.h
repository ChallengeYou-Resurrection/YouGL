#pragma once

#include <SFML/Graphics.hpp>
#include "../Maths/GlmCommon.h"
#include "Transform.h"

class Controller;

class Camera
{
    public:
        Camera();

        void input(const Controller& controller);
        void update(float dt);

        const glm::vec3& getPositon() const;
        const glm::vec3& getRotation() const;
        const glm::mat4& getProjectionMatrix() const;

    private:
        Transform m_transform;

        glm::mat4 m_projectionMatrix;
};