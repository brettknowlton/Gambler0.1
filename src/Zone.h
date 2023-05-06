#pragma once

#include <vector>
#include <memory>
#include "Tile.h"
#include "Collider.h"
#include "Enemy.h"

namespace game {

    class Zone {
    public:
        Zone(int x, int y);
        ~Zone();

        void Tick(float dt);
        void Render(const Renderer& renderer);

        //void AddTile(std::shared_ptr<Tile> tile);
        //void RemoveTile(std::shared_ptr<Tile> tile);

        void LoadColliders(const std::string& path);
        void AddCollider(std::shared_ptr<Collider> collider);
        void RemoveCollider(std::shared_ptr<Collider> collider);

        //void AddEnemy(std::shared_ptr<Enemy> enemy);
        //void RemoveEnemy(std::shared_ptr<Enemy> enemy);

        int GetX() { return x; }
        int GetY() { return y; }
        std::string GetZoneID() { return zoneID; }

    private:
        std::vector<std::shared_ptr<Tile>> m_Tiles;
        std::vector<std::shared_ptr<Collider>> m_Colliders;
        //std::vector<std::shared_ptr<Enemy>> m_Enemies;

        int x, y;
        std::string zoneID;
    };
}