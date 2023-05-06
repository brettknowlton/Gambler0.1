#include "World.h"

namespace game{

World::World(int zoneWidth, int zoneHeight)
: zoneWidth(zoneWidth), zoneHeight(zoneHeight)
{
    zones.resize(zoneWidth, std::vector<std::shared_ptr<Zone>>(zoneHeight, nullptr));

}

World::~World() {
}

void World::Tick() {
    for (auto& row : zones) {
        for (auto& zone : row) {
            if (zone != nullptr) {
                zone->Tick();
            }
        }
    }
}

void World::Render() {
    for (auto& row : zones) {
        for (auto& zone : row) {
            if (zone != nullptr) {
                zone->Render();
            }
        }
    }
}

void World::LoadZone(int x, int y) {
    if (IsZoneLoaded(x, y)) {
        return;
    }

    zones[x][y] = std::make_shared<Zone>(x, y);
    LoadAdjacentZones(x, y);
}

void World::UnloadZone(int x, int y) {
    if (!IsZoneLoaded(x, y)) {
        return;
    }

    zones[x][y] = nullptr;
}

bool World::IsZoneLoaded(int x, int y) {
    return zones[x][y] != nullptr;
}

void World::LoadAdjacentZones(int x, int y) {
    if (x > 0) {
        LoadZone(x - 1, y);
    }
    if (x < zoneWidth - 1) {
        LoadZone(x + 1, y);
    }
    if (y > 0) {
        LoadZone(x, y - 1);
    }
    if (y < zoneHeight - 1) {
        LoadZone(x, y + 1);
    }
}

} // namespace game