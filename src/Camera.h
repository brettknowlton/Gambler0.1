#pragma once

namespace game {

class Camera {
public:
    Camera(int screenWidth, int screenHeight);
    ~Camera();

    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetScreenWidth() const { return screenWidth; }
    int GetScreenHeight() const { return screenHeight; }

    void SetPosition(int x, int y);

    glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
    glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
    glm::mat4 GetViewProjectionMatrix() const { return m_ProjectionMatrix * m_ViewMatrix; }

private:
    int x, y;
    int screenWidth, screenHeight;

    glm::mat4 m_ProjectionMatrix;
    glm::mat4 m_ViewMatrix;
};

} // namespace game
