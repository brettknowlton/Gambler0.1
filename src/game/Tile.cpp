#include "Tile.h"
#include "renderer/Shader.h"
#include "camera.h"

namespace game{
    Tile::Tile(int x, int y, unsigned int tileID, const std::shared_ptr<Texture>& textureAtlas, const std::shared_ptr<Shader>& shader)
    : m_X(x), m_Y(y), m_TextureAtlas(textureAtlas), m_TileShader(shader)
    {
        //all tiles will be in the same tile atlas so we will have a standard UV coordinate step
        //use TILE_SIZE to get the correct UV coordinates
        //tileID 0 is the bottom left tile in the atlas
        //tileID 1 is the tile to the right of the bottom left tile in the atlas
        //make sure to use the correct UV coordinates for the tileID
        
        m_U = (tileID % (m_TextureAtlas->GetWidth() / TILE_SIZE)) * (1.0f / (m_TextureAtlas->GetWidth() / TILE_SIZE));
        m_V = (tileID / (m_TextureAtlas->GetWidth() / TILE_SIZE)) * (1.0f / (m_TextureAtlas->GetWidth() / TILE_SIZE));


        // std::cout<< "Tile created at: " << x << ", " << y << " with ID: " << tileID << " and UV: " << u << ", " << v << "\n";

        
    }
    Tile::~Tile(){
    }

    void Tile::SubmitToBatchRenderer(BatchRenderer& batchRenderer) const{
        float posX = static_cast<float>(m_X * TILE_SIZE);
        float posY = static_cast<float>(m_Y * TILE_SIZE);
        float uvStep = 1.0f / static_cast<float>(m_TextureAtlas->GetWidth() / TILE_SIZE);

        float vertices[] = {
            posX, posY, m_U, m_V,
            posX + TILE_SIZE, posY, m_U + uvStep, m_V,
            posX + TILE_SIZE, posY + TILE_SIZE, m_U + uvStep, m_V + uvStep,
            posX, posY + TILE_SIZE, m_U, m_V + uvStep
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        batchRenderer.Submit(vertices, 4 * 4, indices, 6);
    }

    void Tile::Tick(float dt){
    }

}