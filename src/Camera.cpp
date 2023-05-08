#include "Camera.h"

namespace game {

Camera::Camera(int screenWidth, int screenHeight)
    : x(0), y(0), screenWidth(screenWidth), screenHeight(screenHeight), m_ProjectionMatrix(glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f)), m_ViewMatrix(1.0f) 
{

}

Camera::~Camera() {
}

void Camera::SetPosition(int x, int y) {
    this->x = x;
    this->y = y;
    m_ViewMatrix = glm::translate(glm::identity<glm::mat4>(), glm::vec3(-x, -y, 0));
}

} // namespace game
