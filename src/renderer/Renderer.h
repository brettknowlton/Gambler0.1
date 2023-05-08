#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

    class Renderer
    {
        public:
            void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
            void BatchedDraw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, unsigned int count) const;
            void Clear() const;
            Renderer Get() const;
    };

