#include "TestPlayer.h"
#include "GLMacros.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test{

        TestPlayer::TestPlayer ()
        :m_Camera(512, 288), m_World(1, 1), m_Translation(0,0,0), m_Player(glm::vec2(0, 0), 32, 32)
        {
            m_Camera.SetPosition(0,0);
        
        }

        TestPlayer::~TestPlayer ()
        {
        }
    
        void TestPlayer::OnUpdate(float deltaTime)
        {
            //tick or update
            m_World.Tick(deltaTime);

            if(KEYLOOKUP(GLFW_KEY_W) == GLFW_PRESS) {
                m_Player.MoveUp();
            }
            if (KEYLOOKUP(GLFW_KEY_S) == GLFW_PRESS) {
                m_Player.MoveDown();
            }
            if (KEYLOOKUP(GLFW_KEY_A) == GLFW_PRESS) {
                m_Player.MoveLeft();
            }
            if (KEYLOOKUP(GLFW_KEY_D) == GLFW_PRESS) {
                m_Player.MoveRight();
            }

        // Update
            m_Player.Tick(0.16f);
            m_Camera.SetPosition(m_Player.GetPosition().x, m_Player.GetPosition().y);
            m_Camera.Tick(0.16f);
        }
    
        void TestPlayer::OnRender(Renderer renderer)
        {
            m_World.Render(renderer, m_Camera);
            // m_Player.Render(renderer, m_Camera);
        }
    
        void TestPlayer::OnImGuiRender()
        {
            ImGui::SliderFloat2("Translation", &m_Translation.x, 0.0f, 960.0f);
            ImGui::Text("Application averaging %3.f ms/frame (%.2f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
}