#include "Model.h"

#include "Mesh.h"

Model::Model(Mesh& mesh)
{
    create(mesh);
}

Model::Model(Model&& model)
:   m_buffers(std::move(model.m_buffers))
{
    m_renderData.vao = model.m_renderData.vao;
    model.m_renderData.vao = 0;
}

Model& Model::operator=(Model&& model)
{
    m_renderData.vao = model.m_renderData.vao;
    m_buffers = std::move(model.m_buffers);

    model.m_renderData.vao = 0;
}

Model::~Model()
{
    if (m_renderData.vao) {
        glDeleteVertexArrays(1, &m_renderData.vao);
        glDeleteBuffers(m_buffers.size(), m_buffers.data());
    }
}

void Model::create(Mesh& mesh)
{
    auto createBuffer = [this](uint8_t index, uint8_t numDataPerPoint, const std::vector<GLfloat>& data)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_buffers[index]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), data.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, numDataPerPoint, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
        glEnableVertexAttribArray(0);
    };

    glGenBuffers(1, m_buffers.data());
    createBuffer(0, 3, mesh.verticies);
    createBuffer(1, 2, mesh.texCoords);
    createBuffer(2, 3, mesh.normals);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_buffers[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh.indices[0]) * mesh.indices.size(), mesh.indices.data(), GL_STATIC_DRAW);
}

const RenderData & Model::getRenderData() const
{
    return m_renderData;
}



