#include "Camera.h"

#include "../Maths/Matrix.h"
#include "../Input/Controller.h"

Camera::Camera()
    :   m_projectionMatrix(makeProjectionMatrix())
{ }

void Camera::input(const Controller& controller)
{
	m_velocity = glm::vec3(0,0,0);
    float speed = 0.01f;
    if (controller.forwardPressed()) {
        m_velocity.x += -glm::cos(glm::radians(m_transform.rotation.y + 90)) * speed;
        m_velocity.z += -glm::sin(glm::radians(m_transform.rotation.y + 90)) * speed;
    }
    if (controller.backPressed()) {
        m_velocity.x += glm::cos(glm::radians(m_transform.rotation.y + 90)) * speed;
        m_velocity.z += glm::sin(glm::radians(m_transform.rotation.y + 90)) * speed;
    }
    if (controller.leftPressed()) {
        m_velocity.x += -glm::cos(glm::radians(m_transform.rotation.y)) * speed;
        m_velocity.z += -glm::sin(glm::radians(m_transform.rotation.y)) * speed;
    }
    if (controller.rightPressed()) {
        m_velocity.x += glm::cos(glm::radians(m_transform.rotation.y)) * speed;
        m_velocity.z += glm::sin(glm::radians(m_transform.rotation.y)) * speed;
    }
    if (controller.jumpPressed()) {
        m_velocity.y += speed;
    }
    if (controller.downPressed()) {
        m_velocity.y -= speed;
    }

    m_transform.rotation += controller.getLookChange();
}

void Camera::update(float dt)
{

}

void Camera::applyVelocity()
{
	m_transform.position += m_velocity;
}

void Camera::setVelocity(const glm::vec3 & vel)
{
	m_velocity = vel;
}

const glm::vec3& Camera::getPositon() const
{
    return m_transform.position;
}

const glm::vec3& Camera::getVelocity() const
{
	return m_velocity;
}

const glm::vec3& Camera::getRotation() const
{
    return m_transform.rotation;
}

const glm::mat4& Camera::getProjectionMatrix() const
{
    return m_projectionMatrix;
}
