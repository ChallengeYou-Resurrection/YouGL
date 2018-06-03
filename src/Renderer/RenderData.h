#pragma once

#include <glad.h>

class Model;
class RenderData
{
        friend class Model;
    public:
        void bind() const
        {
            glBindVertexArray(vao);
        }

        GLuint getIndicesCount() const
        {
            return indicesCount;
        }

    private:
        GLuint vao = 0;
        GLuint indicesCount = 0;

};