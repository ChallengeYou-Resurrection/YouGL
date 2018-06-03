#include "Camera.h"

#include "../Maths/Matrix.h"

Camera::Camera()
    :   m_projectionMatrix(makeProjectionMatrix())
{ }

const glm::vec3& Camera::getPositon() const
{
    return m_position;
}

const glm::vec3& Camera::getRotation() const
{
    return m_rotation;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
    return m_projectionMatrix;
}
