#pragma once

#include <vector>
#include "Tile.h"

namespace game {

class Collider {
public:
    Collider(int x, int y, int width, int height);
    ~Collider();

    virtual void Tick(float dt);
    void Render(Renderer& renderer);

    int GetX() { return x; }
    int GetY() { return y; }
    int GetWidth() { return width; }
    int GetHeight() { return height; }

private:
    int x, y, width, height;
    //std::vector<std::shared_ptr<Tile>> tiles;
};
}//namespace game