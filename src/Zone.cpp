#include "Zone.h"

namespace game{
    Zone::Zone(int x, int y)
    : x(x), y(y), zoneID("Zone_" + std::to_string(x) + "_" + std::to_string(y))
    {
        std::string colliderPath = "res/textures/ZoneC" + std::to_string(x) + std::to_string(y) + ".png";
        LoadColliders(colliderPath);

        std::string enemyPath = "res/textures/ZoneE" + std::to_string(x) + std::to_string(y) + ".png";
        
        std::string tilePath = "res/textures/ZoneT" + std::to_string(x) + std::to_string(y) + ".png";

    }

    Zone::~Zone()
    {
    }

    void Zone::Tick(float dt)
    {
        //we may not need to tick all of these, but we'll see
        // for (auto& tile : tiles)
        //     tile->Tick(dt);
        for (auto& collider : m_Colliders)
            collider->Tick(dt);
        // for (auto& enemy : enemies)
        //     enemy->Tick(dt);
    }

    void Zone::Render(const Renderer& renderer)
    {
        for (auto& tile : m_Tiles)
            tile->Render(renderer);

        #ifdef GAMBLER_DEBUG
        for (auto& collider : colliders)//very optional to render colliders, probably only in debug mode
            collider->Render(renderer);
        #endif

        // for (auto& enemy : enemies)
        //     enemy->Render();
    }

    void Zone::LoadColliders(const std::string& imagePath)
    {
        int width, height, channels;
        unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

        if (data) {
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    int index = (y * width + x) * channels;
                    unsigned char r = data[index];
                    unsigned char g = data[index + 1];
                    unsigned char b = data[index + 2];

                    // If the pixel is black (r, g, and b are 0), create a collider
                    if (r == 0 && g == 0 && b == 0) {
                        auto collider = std::make_shared<Collider>(x * Tile::TILE_SIZE, y * Tile::TILE_SIZE, Tile::TILE_SIZE, Tile::TILE_SIZE);
                        m_Colliders.push_back(collider);
                    }
                }
            }
            stbi_image_free(data);
        } else {
        std::cerr << "Failed to load collision map image: " << imagePath << std::endl;
    }

    }
}