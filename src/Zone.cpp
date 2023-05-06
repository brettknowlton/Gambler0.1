#include "Zone.h"

namespace game{
    Zone::Zone(int x, int y)
    : x(x), y(y)
    {
    }

    Zone::~Zone()
    {
    }

    void Zone::Tick()
    {
        //we may not need to tick all of these, but we'll see
        for (auto& tile : tiles)
            tile->Tick();
        for (auto& collider : colliders)
            collider->Tick();
        for (auto& enemy : enemies)
            enemy->Tick();
    }

    void Zone::Render()
    {
        for (auto& tile : tiles)
            tile->Render();

        #ifdef GAMBLER_DEBUG
        for (auto& collider : colliders)//very optional to render colliders, probably only in debug mode
            collider->Render();
        #endif

        for (auto& enemy : enemies)
            enemy->Render();
    }

}