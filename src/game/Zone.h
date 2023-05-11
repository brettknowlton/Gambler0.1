#pragma once

#include <vector>
#include <memory>
#include "Tile.h"
#include "Collider.h"
#include "Enemy.h"
#include "Camera.h"
#include "renderer/BatchRenderer.h"

namespace game {

    class Zone {
    public:
        Zone(int x, int y, const std::shared_ptr<Shader>& shader, const std::shared_ptr<Texture>& textureAtlas);
        ~Zone();

        void Tick(float dt);
        void Render(BatchRenderer& renderer, const Camera& camera) const;

        //void AddTile(std::shared_ptr<Tile> tile);
        //void RemoveTile(std::shared_ptr<Tile> tile);

        void LoadColliders(const std::string& path);
        void LoadTiles(const std::string& tilesImagePath);

        std::shared_ptr<Shader> GetTileShader() { return m_TileShader; }

        //void AddEnemy(std::shared_ptr<Enemy> enemy);
        //void RemoveEnemy(std::shared_ptr<Enemy> enemy);

        int GetX() { return x; }
        int GetY() { return y; }
        std::string GetZoneID() { return zoneID; }
        std::vector<std::shared_ptr<Tile>> GetTiles() { return m_Tiles; }

    private:
        std::shared_ptr<BatchRenderer> m_BatchRenderer;
        std::shared_ptr<Shader> m_TileShader;
        std::shared_ptr<Texture> m_TextureAtlas;
        std::vector<std::shared_ptr<Tile>> m_Tiles;
        std::vector<std::shared_ptr<Collider>> m_Colliders;
        
        //std::vector<std::shared_ptr<Enemy>> m_Enemies;

        int x, y;
        std::string zoneID;

        #ifdef GAMBLER_DEBUG
        std::shared_ptr<Texture> m_ColliderTexture;
        #endif
    };
}