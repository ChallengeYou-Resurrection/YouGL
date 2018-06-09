#include "Camera.h"

#include "../Maths/Matrix.h"
#include "../Input/Controller.h"

Camera::Camera()
    :   m_projectionMatrix(makeProjectionMatrix())
{ }

void Camera::input(const Controller& controller)
{
    float speed = 0.01f;
    if (controller.forwardPressed()) {
        m_transform.position.x += -glm::cos(glm::radians(m_transform.rotation.y + 90)) * speed;
        m_transform.position.z += -glm::sin(glm::radians(m_transform.rotation.y + 90)) * speed;
    }
    if (controller.backPressed()) {
        m_transform.position.x += glm::cos(glm::radians(m_transform.rotation.y + 90)) * speed;
        m_transform.position.z += glm::sin(glm::radians(m_transform.rotation.y + 90)) * speed;
    }
    if (controller.leftPressed()) {
        m_transform.position.x += -glm::cos(glm::radians(m_transform.rotation.y)) * speed;
        m_transform.position.z += -glm::sin(glm::radians(m_transform.rotation.y)) * speed;
    }
    if (controller.rightPressed()) {
        m_transform.position.x += glm::cos(glm::radians(m_transform.rotation.y)) * speed;
        m_transform.position.z += glm::sin(glm::radians(m_transform.rotation.y)) * speed;
    }
    if (controller.jumpPressed()) {
        m_transform.position.y += speed;
    }
    if (controller.downPressed()) {
        m_transform.position.y -= speed;
    }

    m_transform.rotation += controller.getLookChange();
}

void Camera::update(float dt)
{

}

const glm::vec3& Camera::getPositon() const
{
    return m_transform.position;
}

const glm::vec3& Camera::getRotation() const
{
    return m_transform.rotation;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
    return m_projectionMatrix;
}
