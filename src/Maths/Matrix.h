#pragma once

#include "GlmCommon.h"

class Camera;

glm::mat4 makeModelMatrix(const glm::vec3& position, const glm::vec3 rotation);
glm::mat4 makeViewMatrix(const Camera& camera);
glm::mat4 makeProjectionMatrix();
