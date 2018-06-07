#include "Shader.h"

#include "ShaderLoader.h"

Shader::Shader(const char* vertexFileName, const char* fragFileName)
    : m_shaderID(loadShaders(vertexFileName, fragFileName))
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
    m_shaderID = loadShaders(vertexFileName, fragFileName);
}

void Shader::setParameter(const char* name, const glm::mat4& value)
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

GLuint Shader::getUniformLocation(const char* name)
{
    std::string nameStr = name;
    auto itr = m_uniformLocations.find(nameStr);
    if (itr == m_uniformLocations.end()) {
        GLuint location = glGetUniformLocation(m_shaderID, name);
        m_uniformLocations.emplace(nameStr, location);
        return location;
    }
    else {
        return itr->second;
    }
}