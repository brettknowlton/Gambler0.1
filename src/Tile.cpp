#include "Tile.h"
#include "renderer/Shader.h"

namespace game{
    Tile::Tile(int x, int y, float u, float v, const std::shared_ptr<Texture>& textureAtlas)
    : m_X(x), m_Y(y), m_U(u), m_V(v), m_TextureAtlas(textureAtlas)
    {
        float posX = static_cast<float>(x * TILE_SIZE);
        float posY = static_cast<float>(y * TILE_SIZE);
        
        float vertices[] = {
            posX, posY, 0.0f, m_U, m_V,
            posX + TILE_SIZE, posY, 0.0f, m_U + 0.0625f, m_V,
            posX + TILE_SIZE, posY + TILE_SIZE, 0.0f, m_U + 0.0625f, m_V + 0.0625f,
            posX, posY + TILE_SIZE, 0.0f, m_U, m_V + 0.0625f
        };
        
        m_VBO = std::make_unique<VertexBuffer>(vertices, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VBO, layout);

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        m_IBO = std::make_unique<IndexBuffer>(indices, 6);
    }
    Tile::~Tile(){
    }

    void Tile::Render(const Renderer& renderer) const{
        m_TextureAtlas->Bind();
        renderer.Draw(*m_VAO, *m_IBO, *new Shader("../../res/shaders/Basic.shader"));
    }

    void Tile::Tick(float dt){
    }
}