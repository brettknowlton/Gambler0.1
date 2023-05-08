#pragma once

#include <vector>
#include <memory>
#include "Zone.h"
#include "Camera.h"
#include "renderer/BatchRenderer.h"

namespace game{
    
class World
{
public:
    constexpr static int ZONE_WIDTH_IN_TILES = 100;

    World(int zoneWidth, int zoneHeight);
    ~World();
    
    void addZone(std::shared_ptr<Zone> zone);
    void removeZone(std::shared_ptr<Zone> zone);
    
    void Tick(float dt);
    void Render(const Renderer& renderer, const Camera& camera);

private:
    std::vector<std::shared_ptr<Zone>> zones;
    std::shared_ptr<Shader> m_TileShader;

    std::shared_ptr<Texture> m_TextureAtlas;

    BatchRenderer m_BatchRenderer;

    int zoneWidth, zoneHeight;
    bool IsZoneLoaded(std::shared_ptr<Zone> zone);
    bool IsZoneVisible(std::shared_ptr<Zone> zone, const Camera& camera);
    void RenderAdjacentZones(const Renderer& renderer, std::shared_ptr<Zone> zone, const Camera& camera);
    
};
}
