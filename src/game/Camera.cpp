#include "Camera.h"

namespace game {

Camera::Camera(int screenWidth, int screenHeight)
    : m_X(0), m_Y(0), screenWidth(screenWidth), screenHeight(screenHeight), m_ProjectionMatrix(glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f)), m_ViewMatrix(1.0f) 
{

}

Camera::~Camera() {
}


void Camera::Tick(float deltaTime)
{
    m_ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-m_X, -m_Y, 0.0f));
}

void Camera::SetPosition(int x, int y) {
    //center camera on position
    m_X = x - (screenWidth / 2);
    m_Y = y - (screenHeight / 2);
}

} // namespace game
