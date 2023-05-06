#pragma once

#include <vector>
#include "Tile.h"
#include "renderer/Renderer.h"
#include "renderer/Texture.h"

namespace game {

class Collider {
public:
    Collider(int x, int y, int width, int height);
    ~Collider();

    virtual void Tick(float dt);
    void Render(const Renderer& renderer);

    int GetX() { return x; }
    int GetY() { return y; }
    int GetWidth() { return width; }
    int GetHeight() { return height; }

private:
    int x, y, width, height;

    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_IBO;
};
}//namespace game