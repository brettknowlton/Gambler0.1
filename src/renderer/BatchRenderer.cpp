#include "BatchRenderer.h"
#include "VertexBufferLayout.h"

BatchRenderer::BatchRenderer(vertexBufferSize, size_t indexBufferSize)
    : m_VBO(vertexBufferSize, nullptr), m_IBO(indexBufferSize, nullptr),
      m_VertexBufferCapacity(vertexBufferSize), m_IndexBufferCapacity(indexBufferSize),
      m_VertexBufferIndex(0), m_IndexBufferIndex(0), m_IndicesRendered(0)
{
    VertexBufferLayout layout;
    layout.Push<float>(2); // position
    layout.Push<float>(2); // texture coordinates
    m_VAO.AddBuffer(m_VBO, layout);
}

void BatchRenderer::Begin()
{
    m_VertexBufferIndex = 0;
    m_IndexBufferIndex = 0;
    m_IndicesRendered = 0;
}

void BatchRenderer::Submit(const float* vertexData, size_t vertexCount, const unsigned int* indexData, size_t indexCount)
{
    if (m_VertexBufferIndex + vertexCount * sizeof(float) > m_VertexBufferCapacity ||
        m_IndexBufferIndex + indexCount * sizeof(unsigned int) > m_IndexBufferCapacity)
    {
        return;
    }

    memcpy((char*)m_VBO.GetBuffer() + m_VertexBufferIndex, vertexData, vertexCount * sizeof(float));
    memcpy((char*)m_IBO.GetBuffer() + m_IndexBufferIndex, indexData, indexCount * sizeof(unsigned int));

    m_VertexBufferIndex += vertexCount * sizeof(float);
    m_IndexBufferIndex += indexCount * sizeof(unsigned int);
    m_IndicesRendered += indexCount;
}

void BatchRenderer::End()
{
    m_VBO.UnmapBuffer();
    m_IBO.UnmapBuffer();
}

void BatchRenderer::Render(const Renderer& renderer)
{
    renderer.Draw(m_VAO, m_IBO, m_IndicesRendered);
}