#pragma once

#include <glad.h>
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

    protected:
        GLuint getUniformLocation(const char* name);

        void setMatrixParam(GLuint location, const glm::mat4& param);

    private:
        GLuint m_shaderID = 0;
};