#pragma once

#include <memory>

#include "renderer/Renderer.h"
#include "renderer/Texture.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/VertexBufferLayout.h"
#include "renderer/IndexBuffer.h"

namespace game {

class Tile {
public:
    static constexpr int TILE_SIZE = 16;

    Tile(int x, int y, float u, float v, const std::shared_ptr<Texture>& textureAtlas);
    ~Tile();

    void Render(const Renderer& renderer) const;
    void Tick(float dt);

    int GetX() const { return m_X; }
    int GetY() const { return m_Y; }

private:
    int m_X, m_Y;
    float m_U, m_V;
    std::shared_ptr<Texture> m_TextureAtlas;
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_IBO;
};
}