#include "Player.h"

namespace game{


Player::Player(glm::vec2 position, float width, float height)
    : m_Position(position), m_Width(width), m_Height(height)
{
    m_Velocity = glm::vec2(0.0f);
}

void Player::Tick(float deltaTime)
{
    m_Position += m_Velocity * deltaTime;
    m_Velocity = glm::vec2(0.0f);
    
}
void Player::Render()
{
    GLCall(glBegin(GL_QUADS));
    GLCall(glVertex2f(m_Position.x, m_Position.y));
    GLCall(glVertex2f(m_Position.x + m_Width, m_Position.y));
    GLCall(glVertex2f(m_Position.x + m_Width, m_Position.y + m_Height));
    GLCall(glVertex2f(m_Position.x, m_Position.y + m_Height));
    GLCall(glEnd());
}

void Player::OnImGuiRender()
{
    ImGui::SliderFloat("Player Width", &m_Width, 10.0f, 100.0f);
    ImGui::SliderFloat("Player Height", &m_Height, 10.0f, 100.0f);
}

void Player::MoveUp()
{
    m_Velocity.y = -1.0f;
}

void Player::MoveDown()
{
    m_Velocity.y = 1.0f;
}

void Player::MoveLeft()
{
    m_Velocity.x = -1.0f;
}

void Player::MoveRight()
{
    m_Velocity.x = 1.0f;
}


}