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
			glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);
        }

        GLuint getIndicesCount() const
        {
            return indicesCount;
        }

		void setMode(GLenum m)
		{
			this->m_mode = m;
		}

		GLenum getMode() const
		{
			return m_mode;
		}



    private:
        GLuint vao = 0;
		GLuint textureID = 0;
        GLuint indicesCount = 0;

		GLenum m_mode = GL_TRIANGLES;
};