#include "World.h"

namespace game{

World::World(int zoneWidth, int zoneHeight)
: zoneWidth(zoneWidth), zoneHeight(zoneHeight), m_TileShader(std::make_shared<Shader>("../../res/shaders/Basic.shader")),
m_BatchRenderer(100000, 100000)
{
    zones.resize(zoneWidth * zoneHeight);
    //create textureAtlas
    m_TextureAtlas = std::make_shared<Texture>("../../res/textures/Atlas.png", 0);

    //add zones manually, not sure if this is the best way to do it
    zones[0] = std::make_shared<Zone>(0, 0, m_TileShader, m_TextureAtlas);



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

void World::Render(const Renderer& renderer, const Camera& camera) {
    //this assumes that m_BatchRenderer.Begin() has already been called
    //m_BatchRenderer.Begin();
    m_TileShader->Bind();
    m_TileShader->SetUniformMat4f("u_ViewProjection", camera.GetViewProjectionMatrix());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_TextureAtlas->GetID());

    m_TileShader->SetUniform1i("u_Texture", 0);

    for(const auto& zone : zones) 
    {
        if(IsZoneVisible(zone, camera)) {
            zone->Render(m_BatchRenderer, camera);
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

void World::RenderAdjacentZones(const Renderer& renderer, std::shared_ptr<Zone> zone, const Camera& camera) {

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
        if(IsZoneLoaded(zones[x + y * zoneWidth]) && IsZoneVisible(zones[x + y * zoneWidth], camera)) {
            zones[x + y * zoneWidth]->Render(m_BatchRenderer, camera);
        }
    }

}

bool World::IsZoneVisible(std::shared_ptr<Zone> zone, const Camera& camera) {
    
        //calculate the x and y coordinates of the zone
        int x = zone->GetX() * ZONE_WIDTH_IN_TILES * 16;
        int y = zone->GetY() * ZONE_WIDTH_IN_TILES * 16;
    
        //if the zone is within the camera's view, return true
        if(x + camera.GetScreenWidth() > camera.GetX() && x < camera.GetX() + camera.GetScreenWidth() &&
        y + camera.GetScreenHeight() > camera.GetY() && y < camera.GetY() + camera.GetScreenHeight()) {
            return true;
        }
    
        //otherwise, return false
        return false;
}




} // namespace game