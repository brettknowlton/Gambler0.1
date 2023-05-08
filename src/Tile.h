#pragma once

#include <memory>
#include "Camera.h"

#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/VertexBuffer.h"
#include "renderer/VertexBufferLayout.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexArray.h"
#include "renderer/Renderer.h"

namespace game {

class Tile {
public:
    static constexpr int TILE_SIZE = 16;

    Tile(int x, int y, unsigned int tileID, const std::shared_ptr<Texture>& textureAtlas, const std::shared_ptr<Shader>& shader);
    ~Tile();

    void Render(const Renderer& renderer, const Camera& camera) const;
    void Tick(float dt);

    int GetX() const { return m_X; }
    int GetY() const { return m_Y; }

    void SubmitToBatchRenderer(BatchRenderer& batchRenderer) const;

private:
    int m_X, m_Y;
    float m_U, m_V;

    std::shared_ptr<Shader> m_TileShader;
    std::shared_ptr<Texture> m_TextureAtlas;
};
}