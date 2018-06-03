#include "Matrix.h"

#include "../Renderer/Camera.h"


glm::mat4 makeModelMatrix(const glm::vec3& position, const glm::vec3 rotation)
{
    glm::mat4 matrix;

    matrix = glm::rotate(matrix, glm::radians(rotation.x), { 1, 0, 0 });
    matrix = glm::rotate(matrix, glm::radians(rotation.y), { 0, 1, 0 });
    matrix = glm::rotate(matrix, glm::radians(rotation.z), { 0, 0, 1 });

    matrix = glm::translate(matrix, position);

    return matrix;
}

glm::mat4 makeViewMatrix(const Camera& camera)
{
    glm::mat4 matrix;

    matrix = glm::rotate(matrix, glm::radians(camera.getRotation().x), { 1, 0, 0 });
    matrix = glm::rotate(matrix, glm::radians(camera.getRotation().y), { 0, 1, 0 });
    matrix = glm::rotate(matrix, glm::radians(camera.getRotation().z), { 0, 0, 1 });

    matrix = glm::translate(matrix, -camera.getPositon());

    return matrix;
}

glm::mat4 makeProjectionMatrix()
{;
    return glm::perspective(glm::radians(90.0f), 1280.0f / 720.0f, 0.1f, 256.0f);
}