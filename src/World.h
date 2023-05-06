#pragma once

#include <vector>
#include <memory>
#include "Zone.h"

namespace game{
    
class World
{
public:
    World(int zoneWidth, int zoneHeight);
    ~World();
    
    void addZone(std::shared_ptr<Zone> zone);
    void removeZone(std::shared_ptr<Zone> zone);
    
    void Tick(float dt);
    void Render(const Renderer& renderer);

private:
    std::vector<std::shared_ptr<Zone>> zones;
    int zoneWidth, zoneHeight;

    bool IsZoneLoaded(std::shared_ptr<Zone> zone);
    void RenderAdjacentZones(std::shared_ptr<Zone> zone, const Renderer& renderer);
};
}
