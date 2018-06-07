#pragma once

#include "GlmCommon.h"

class Camera;
struct Transform;

glm::mat4 makeModelMatrix(const Transform& transform);
glm::mat4 makeViewMatrix(const Camera& camera);
glm::mat4 makeProjectionMatrix();
