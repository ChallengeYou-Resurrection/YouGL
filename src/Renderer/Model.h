#pragma once

#include <array>
#include <vector>
#include <glad.h>

#include "../Util/NonCopyable.h"
#include "RenderData.h"

struct Mesh;

class Model : public NonCopyable
{
    public:
        Model() = default;
        Model(Mesh& mesh);
        Model(Model&& model);
        Model& operator =(Model&& model);
        ~Model();

        void create(Mesh& mesh);
		void create(Mesh& mesh, GLuint textureID);
        const RenderData& getRenderData() const;

		void setMode(GLenum m);

    private:
        RenderData m_renderData;
        std::array<GLuint, 5> m_buffers;
};