#include "StaticModelShader.h"

void StaticModelShader::init()
{
    create("StaticModel", "StaticModel");

    m_locModelMatrix = getUniformLocation("modelMatrix");
    m_locViewMatrix = getUniformLocation("viewMatrix");
    m_locProjMatrix = getUniformLocation("projMatrix");
}

void StaticModelShader::setModelMatrix(const glm::mat4 & modelMatrix)
{
    setMatrixParam(m_locModelMatrix, modelMatrix);
}

void StaticModelShader::setViewMatrix(const glm::mat4 & viewMatrix)
{
    setMatrixParam(m_locViewMatrix, viewMatrix);
}

void StaticModelShader::setProjMatrix(const glm::mat4 & projMatrix)
{
    setMatrixParam(m_locProjMatrix, projMatrix);
}
