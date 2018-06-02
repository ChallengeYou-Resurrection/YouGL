#include "Camera.h"

Camera::Camera()
{

}

const glm::vec3 & Camera::getPositon() const
{
    return m_position;
}

const glm::vec3 & Camera::getRotation() const
{
    return m_rotation;
}
