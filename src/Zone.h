#pragma once

#include <vector>
#include "Tile.h"
#include "Collider.h"
#include "Enemy.h"

namespace game {

    class Zone {
    public:
        Zone(int x, int y);
        ~Zone();

        void Tick();
        void Render();

        void AddTile(std::shared_ptr<Tile> tile);
        void RemoveTile(std::shared_ptr<Tile> tile);

        void AddCollider(std::shared_ptr<Collider> collider);
        void RemoveCollider(std::shared_ptr<Collider> collider);

        void AddEnemy(std::shared_ptr<Enemy> enemy);
        void RemoveEnemy(std::shared_ptr<Enemy> enemy);

        int GetX() { return x; }
        int GetY() { return y; }

    private:
        std::vector<std::shared_ptr<Tile>> tiles;
        std::vector<std::shared_ptr<Collider>> colliders;
        std::vector<std::shared_ptr<Enemy>> enemies;

        int x, y;
    };
}