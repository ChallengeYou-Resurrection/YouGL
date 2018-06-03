#pragma once

#include "Shader.h"

class StaticModelShader : public Shader
{
    public:
        void init();

        void setModelMatrix(const glm::mat4& modelMatrix);
        void setViewMatrix(const glm::mat4& viewMatrix);
        void setProjMatrix(const glm::mat4& projMatrix);

    private:
        GLuint m_locModelMatrix;
        GLuint m_locViewMatrix;
        GLuint m_locProjMatrix;
};