#pragma once
#include "glm/glm.hpp"

namespace game{
class Player {
public:
    Player(glm::vec2 position, float width, float height);

    void Tick(float deltaTime);
    void Render();
    void OnImGuiRender();

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    glm::vec2 GetPosition() const { return m_Position; }
    glm::vec2 GetSize() const { return glm::vec2(m_Width, m_Height); }

private:
    glm::vec2 m_Position;
    glm::vec2 m_Velocity;
    float m_Width, m_Height;
};
}