#include "Shader.h"

#include "ShaderLoader.h"

Shader::Shader(const char* vertexFileName, const char* fragFileName)
    : m_shaderID(loadShader(vertexFileName, fragFileName))
{
}

Shader::Shader(Shader && shader)
{
    m_shaderID = shader.m_shaderID;
    shader.m_shaderID = 0;
}

Shader & Shader::operator=(Shader && shader)
{
    m_shaderID = shader.m_shaderID;
    shader.m_shaderID = 0;
    return *this;
}

Shader::~Shader()
{
    glDeleteProgram(m_shaderID);
}

void Shader::bind()
{
    glUseProgram(m_shaderID);
}

void Shader::create(const char* vertexFileName, const char* fragFileName)
{
    m_shaderID = loadShader(vertexFileName, fragFileName)
}
