#pragma once

#include <array>
#include <vector>
#include <glad.h>
#include "../Util/NonCopyable.h"

struct Mesh;

class Model;
class RenderData
{
        friend class Model;
    public:
        void bind()
        {
            glBindVertexArray(vao);
        }

        GLuint getIndicesCount() const
        {
            return indicesCount;
        }

    private:
        GLuint vao;
        GLuint indicesCount;

};

class Model : public NonCopyable
{
    public:
        Model() = default;
        Model(Mesh& mesh);
        Model(Model&& model);
        Model& operator =(Model&& model);
        ~Model();

        void create(Mesh& mesh);
        const RenderData& getRenderData() const;

    private:
        RenderData m_renderData;
        std::array<GLuint, 4> m_buffers;
};