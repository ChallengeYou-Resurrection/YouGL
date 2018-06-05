#pragma once

#include <glad.h>
#include <unordered_map>
#include "../../Util/NonCopyable.h"
#include "../../Maths/GlmCommon.h"

class Shader : public NonCopyable
{
    public:
        Shader() = default;
        Shader(const char* vertexFileName, const char* fragFileName);
        Shader(Shader&& shader);
        Shader& operator=(Shader&& shader);
        ~Shader();

        void bind();

        void create(const char* vertexFileName, const char* fragFileName);

        void setParameter(const char* name, const glm::mat4& value);

    private:
        GLuint getUniformLocation(const char* name);

        std::unordered_map<std::string, GLuint> m_uniformLocations;
        GLuint m_shaderID = 0;
};