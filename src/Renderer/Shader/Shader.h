#pragma once

#include <glad.h>
#include "../../Util/NonCopyable.h"

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

    private:
        GLuint m_shaderID = 0;
};