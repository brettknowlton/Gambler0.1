#include "Collider.h"
#include "renderer/Renderer.h"

namespace game {

Collider::Collider(int x, int y, int width, int height)
    : x(x), y(y), width(width), height(height) {
}

void Collider::Render(Renderer& renderer) {
    // Render the collider here, e.g., by drawing a rectangle
}

void Collider::Tick(float dt){
    // Check for collisions here

} 
}// namespace game