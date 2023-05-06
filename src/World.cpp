#include "World.h"

namespace game{

World::World(int zoneWidth, int zoneHeight)
: zoneWidth(zoneWidth), zoneHeight(zoneHeight)
{
    zones.resize(zoneWidth * zoneHeight);
}

World::~World() {
}

void World::Tick(float dt) {
    for (auto& zone : zones) {
        if (zone != nullptr) {
            zone->Tick(dt);
        }
    }
}

void World::Render(const Renderer& renderer) {
    for (auto& zone : zones) {
        if (zone != nullptr) {
            zone->Render(renderer);
            RenderAdjacentZones(zone, renderer);
        }
    }
}

void World::addZone(std::shared_ptr<Zone> zone) {
    zones[zone->GetX() + zone->GetY() * zoneWidth] = zone;
}

void World::removeZone(std::shared_ptr<Zone> zone) {
    zones[zone->GetX() + zone->GetY() * zoneWidth] = nullptr;
}

bool World::IsZoneLoaded(std::shared_ptr<Zone> zone) {
    return zone != nullptr;
}

void World::RenderAdjacentZones(std::shared_ptr<Zone> zone, const Renderer& renderer) {

    //loop 9 times, once for each adjacent zone plus the center one
    for(int i=0; i<9; i++) {

        //if i is 4, then we are on the center zone, so skip it
        if(i == 4) {
            continue;
        }

        //calculate the x and y offsets for the adjacent zone
        int xOffset = (i % 3) - 1;
        int yOffset = (i / 3) - 1;

        //calculate the x and y coordinates of the adjacent zone
        int x = zone->GetX() + xOffset;
        int y = zone->GetY() + yOffset;

        //if the adjacent zone is loaded, render it
        if(IsZoneLoaded(zones[x + y * zoneWidth])) {
            zones[x + y * zoneWidth]->Render(renderer);
        }
    }

}

} // namespace game