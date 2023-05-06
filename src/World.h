#pragma once

#include <vector>
#include <memory>
#include "Zone.h"

namespace game{
    
class World
public:
    World();
    ~World();
    
    void addZone(std::shared_ptr<Zone> zone);
    void removeZone(std::shared_ptr<Zone> zone);
    
    void update();

private:
    std::vector<std::shared_ptr<Zone>> zones;
    int zoneWidth, zoneHeight;

    bool IsZoneLoaded(int x, int y);
    void LoadAdjacentZones(int x, int y);
};
}
