#include "EditorView.h"

void EditorView::input(const Controller & controller)
{
	switch (m_cameraState) {
		case CameraType::FREEROAM: inputFreeroam(controller); break;
		case CameraType::GRID: inputGridview(controller); break;
		case CameraType::PLAYER: inputPlayer(controller); break;
	}
}

void EditorView::update(float dt, DebugLogGUI& d_gui, u8 floor, GeoOctree& octr)
{
	switch (m_cameraState) {
		case CameraType::GRID: updateGridview(dt, floor); break;
		case CameraType::PLAYER: updatePlayer(dt, d_gui, octr); break;
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

	// Mouse Drag
	if (controller.mouse2Down())
	{
		float mouseDragSpeed = 600.f;

		// Set variables to compare to (when mouse2 is pressed)
		if (m_grid_m2Down == false)
		{
			m_grid_m2Down = true;
			m_grid_startPos = controller.getMousePositionRelativeToWindow();
			m_grid_dragStartVec = m_transform.position;
		}

		// Apply velocity to the startPos for WASD to have an effect
		m_grid_dragStartVec += m_velocity;
		m_velocity = glm::vec3(0, 0, 0);

		// Get the difference in mouse position
		sf::Vector2i mouseDiff = m_grid_startPos - controller.getMousePositionRelativeToWindow();
		glm::vec3 newPos = m_grid_dragStartVec;

		// Apply difference in 3D
		newPos.x += glm::cos(glm::radians(m_transform.rotation.y)) * mouseDiff.x / mouseDragSpeed;
		newPos.x += glm::cos(glm::radians(m_transform.rotation.y + 90)) * mouseDiff.y / mouseDragSpeed;

		newPos.z += glm::sin(glm::radians(m_transform.rotation.y)) * mouseDiff.x / mouseDragSpeed;
		newPos.z += glm::sin(glm::radians(m_transform.rotation.y + 90)) * mouseDiff.y / mouseDragSpeed;

		m_transform.position = newPos;
	}
	else {
		m_grid_m2Down = false;
	}

	// Mouse Rotation
	if (controller.mouse3Down())
	{
		if (m_grid_m3Down == false)
		{
			m_grid_m3Down = true;
			//m_grid_startRay = mRay;

		}

	}
	else {
		m_grid_m3Down = false;
	}

	//m_transform.rotation += controller.getLookChange();
}

// Player Mode
// Todo: Separate Class?

void EditorView::inputPlayer(const Controller & controller)
{
	float speed = 0.1f;

	p_acceleration = glm::vec3(0, 0, 0); //glm::vec3(0, -9.81 * speed, 0);
	//m_velocity = glm::vec3(0,0,0);

	if (controller.forwardPressed()) {
		p_acceleration.x += -glm::cos(glm::radians(m_transform.rotation.y + 90)) * speed;
		p_acceleration.z += -glm::sin(glm::radians(m_transform.rotation.y + 90)) * speed;
	}
	if (controller.backPressed()) {
		p_acceleration.x += glm::cos(glm::radians(m_transform.rotation.y + 90)) * speed;
		p_acceleration.z += glm::sin(glm::radians(m_transform.rotation.y + 90)) * speed;
	}
	if (controller.leftPressed()) {
		p_acceleration.x += -glm::cos(glm::radians(m_transform.rotation.y)) * speed;
		p_acceleration.z += -glm::sin(glm::radians(m_transform.rotation.y)) * speed;
	}
	if (controller.rightPressed()) {
		p_acceleration.x += glm::cos(glm::radians(m_transform.rotation.y)) * speed;
		p_acceleration.z += glm::sin(glm::radians(m_transform.rotation.y)) * speed;
	}
	if (controller.jumpPressed()) {
		p_acceleration.y += speed;
	}
	if (controller.downPressed()) {
		p_acceleration.y -= speed;
	}

	p_velocity += p_acceleration;
	p_velocity.x *= 0.85f;
	p_velocity.y *= 0.90f;
	p_velocity.z *= 0.85f;

	if (fabs(p_velocity.x) < 0.0001f) p_velocity.x = 0.f;
	if (fabs(p_velocity.y) < 0.0001f) p_velocity.y = 0.f;
	if (fabs(p_velocity.z) < 0.0001f) p_velocity.z = 0.f;

	m_transform.rotation += controller.getLookChange();
}

void EditorView::updatePlayer(float dt, DebugLogGUI& d_gui, GeoOctree& octr)
{
	m_velocity = dt * p_velocity;

	glm::vec3 m_startPosition = Coordinate::WorldToLevel(this->m_transform.position);
	glm::vec3 m_endPosition   = Coordinate::WorldToLevel(this->m_transform.position + m_velocity);

	// TODO: Get all node data that intersects with the swept sphere
	std::vector<std::shared_ptr<CYGeneric>> wall_list = octr.getCollisionMeshAtPoint(m_startPosition);
	
	// Insert more walls 
	if (!octr.checkIfTwoPointsInSameOctree(m_startPosition, m_endPosition))
	{
		std::vector<std::shared_ptr<CYGeneric>> extended_wall_list = octr.getCollisionMeshAtPoint(m_endPosition);
		wall_list.insert(wall_list.end(), extended_wall_list.begin(), extended_wall_list.end());
	}

	// Initialize vectors 
	Collision::eSpace::P_CollisionPacket c_pkg;

	c_pkg.playerRadius = glm::vec3(1.f, 2.f, 1.f);

	c_pkg.R3Position    = m_startPosition;
	c_pkg.R3Velocity	= m_velocity;

	glm::vec3 e_velocity = Collision::eSpace::covertToESpace(c_pkg.R3Velocity, c_pkg.playerRadius);
	glm::vec3 e_origin	 = Collision::eSpace::covertToESpace(c_pkg.R3Position, c_pkg.playerRadius);
	c_pkg.e_velocityN	 = glm::normalize(c_pkg.e_velocity);

	glm::vec3 finalPos = Collision::eSpace::collideWithWorld(wall_list, &c_pkg, e_origin, e_velocity, 0);
	d_gui.add3DVector("final pos", Coordinate::LevelToWorld(c_pkg.playerRadius * finalPos));
	d_gui.add3DVector("egg", Coordinate::LevelToWorld(c_pkg.playerRadius * (e_origin)));
	d_gui.add3DVector("supposed", Coordinate::LevelToWorld(m_endPosition));

	// TODO: Proper collision response
	glm::vec3 r3final = c_pkg.playerRadius * finalPos;
	m_velocity = r3final - m_startPosition;
	//this->m_transform.position = Coordinate::LevelToWorld(c_pkg.playerRadius * finalPos);
	//this->m_transform.position = Coordinate::LevelToWorld(c_pkg.playerRadius * (e_origin + e_velocity));
}