#pragma once

#include "../Maths/GlmCommon.h"

class Camera
{
    public:
        Camera();

        const glm::vec3& getPositon() const;
        const glm::vec3& getRotation() const;
        const glm::mat4& getProjectionMatrix() const;

    private:
        glm::vec3 m_position;
        glm::vec3 m_rotation;
        glm::mat4 m_projectionMatrix;
};