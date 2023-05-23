#include "TestPlayer.h"
#include "GLMacros.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "game/ecs/Componenets/CMP_Transform.h"


namespace test{

        TestPlayer::TestPlayer ()
        :m_Camera(512, 288), m_World(1, 1), m_Translation(0,0,0), m_Player()
        {
            m_Camera.SetPosition(0,0);
            m_Player.addComponent(new game::TransformComponent(glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(1,1,1)));//todo make this a smart pointer instead of a raw pointer

        }

        TestPlayer::~TestPlayer ()
        {
        }
    
        void TestPlayer::OnUpdate(float deltaTime)
        {
            
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