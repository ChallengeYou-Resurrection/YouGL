#include "EditorView.h"

void EditorView::input(const Controller & controller)
{
	switch (m_cameraState) {
		case CameraType::FREEROAM: inputFreeroam(controller); break;
		case CameraType::GRID: inputGridview(controller); break;
	}
}

void EditorView::update(float dt, u8 floor)
{
	switch (m_cameraState) {
		case CameraType::GRID: updateGridview(dt, floor); break;
	}

	m_viewMatrix = makeViewMatrix(*this);
}

void EditorView::updateGridview(float dt, u8 floor)
{
	glm::vec3 pos = m_transform.position;
	m_transform.position = Maths::lerp(pos, glm::vec3(pos.x, ((float)floor + 3.5f) * WORLD_HEIGHT / WORLD_SIZE, pos.z), 0.4f);
}

void EditorView::inputFreeroam(const Controller & controller)
{
	m_velocity = glm::vec3(0, 0, 0);
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

void EditorView::inputGridview(const Controller & controller)
{
	m_velocity = glm::vec3(0, 0, 0);
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

	m_transform.rotation += controller.getLookChange();
}
