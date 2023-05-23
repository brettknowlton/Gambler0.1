#include "TestPlayer.h"
//#include "GLMacros.h"
//#include "imgui/imgui.h"
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"

#include "game/ecs/Componenets/CMP_Transform.h"


namespace test{

    TestPlayer::TestPlayer()
        :m_Camera(512, 288), m_World(1, 1)
    {
        //m_Camera.SetPosition(0,0);
        
        m_Player.addComponent(std::make_shared<component::Transform>(glm::vec3(0,0,0))); 
    }

    TestPlayer::~TestPlayer()
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
        ImGui::Text("Application averaging %3.f ms/frame (%.2f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}