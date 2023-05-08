#pragma once

#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "Camera.h"


class BatchRenderer
{
public:
    BatchRenderer(size_t vertexBufferSize, size_t indexBufferSize);

    void Begin();
    void Submit(const float* vertexData, size_t vertexCount, const unsigned int* indexData, size_t indexCount);
    void End();
    void Render(const Renderer& renderer, const game::Camera& camera, const Shader& shader);

private:
    VertexArray m_VAO;
    VertexBuffer m_VBO;
    IndexBuffer m_IBO;

    size_t m_VertexBufferCapacity;
    size_t m_IndexBufferCapacity;

    size_t m_VertexBufferIndex;
    size_t m_IndexBufferIndex;

    unsigned int m_IndicesRendered;
};