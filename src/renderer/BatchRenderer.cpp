#include "BatchRenderer.h"
#include "VertexBufferLayout.h"

BatchRenderer::BatchRenderer(size_t vertexBufferSize, size_t indexBufferSize)
    : m_VBO(nullptr, vertexBufferSize), m_IBO(nullptr, indexBufferSize),
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

    m_VBO.MapBuffer();
    m_IBO.MapBuffer();
}

void BatchRenderer::Submit(const float* vertexData, size_t vertexCount, const unsigned int* indexData, size_t indexCount)
{
    if (m_VertexBufferIndex + vertexCount * sizeof(float) > m_VertexBufferCapacity ||
        m_IndexBufferIndex + indexCount * sizeof(unsigned int) > m_IndexBufferCapacity)
    {
        std::cout << "BatchRenderer::Submit: Buffer overflow" << std::endl;
        return;
    }

    // Calculate the index offset based on the current vertex buffer index
    unsigned int indexOffset = m_VertexBufferIndex / (4 * sizeof(float));

    // Create a new buffer to store the updated indices
    unsigned int* updatedIndices = new unsigned int[indexCount];

    // Apply the offset to the indices
    for (size_t i = 0; i < indexCount; ++i)
    {
        updatedIndices[i] = indexData[i] + indexOffset;
    }

    memcpy((char*)m_VBO.GetData() + m_VertexBufferIndex, vertexData, vertexCount * sizeof(float));
    memcpy((char*)m_IBO.GetData() + m_IndexBufferIndex, updatedIndices, indexCount * sizeof(unsigned int));

    // Don't forget to delete the updatedIndices buffer after copying the data
    delete[] updatedIndices;

    m_VertexBufferIndex += vertexCount * sizeof(float);
    m_IndexBufferIndex += indexCount * sizeof(unsigned int);
    m_IndicesRendered += indexCount;
}

void BatchRenderer::End()
{
    m_VBO.UnmapBuffer();
    m_IBO.UnmapBuffer();
}

void BatchRenderer::Render(const Renderer& renderer, const game::Camera& camera, const Shader& shader)
{
    // std::cout<<"Rendering "<<m_IndicesRendered<<" indices"<<std::endl;
    // std::cout<<"Rendering "<<m_VertexBufferIndex<<" vertices"<<std::endl;
    renderer.Draw(m_VAO, m_IBO, shader);
}