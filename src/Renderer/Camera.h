#pragma once

#include <SFML/Graphics.hpp>
#include "../Maths/Matrix.h"
#include "../Maths/GlmCommon.h"
#include "../Maths/BasicMathFunctions.h"
#include "../Util/Types.h"
#include "Transform.h"

class Controller;

class Camera
{
    public:
        Camera();

        virtual void input(const Controller& controller);
        virtual void update(float dt);

        const glm::vec3& getPositon() const;
        const glm::vec3& getRotation() const;
		const glm::vec3& getVelocity() const;
        const glm::mat4& getProjectionMatrix() const;
		const glm::mat4& getViewMatrix() const;

		void applyVelocity();
		void setVelocity(const glm::vec3& vel);

    protected:
        Transform m_transform;
		glm::vec3 m_velocity;

        glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
};