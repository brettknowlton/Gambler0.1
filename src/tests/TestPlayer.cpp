#include "TestPlayer.h"
//#include "GLMacros.h"
//#include "imgui/imgui.h"
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"

#include "game/ecs/Componenets/CMP_Transform.h"


namespace test{

    TestPlayer::TestPlayer()
        :m_Camera(512, 288), m_World(1, 1), m_BatchRenderer(10000, 10000), m_TileShader(std::make_shared<Shader>("../../res/shaders/Basic.shader"))
    {
        //m_Camera.SetPosition(0,0);
        m_LoadedEntities.push_back(std::make_shared<Entity>(m_Player));
        m_Player.addComponent(std::make_shared<component::Transform>(glm::vec3(0,0,0))); 

    }

    TestPlayer::~TestPlayer()
    {
    }

    void TestPlayer::OnUpdate(float deltaTime)
    {
        m_World.Tick(deltaTime);

        for (auto& entity : m_LoadedEntities) {
            entity->update(deltaTime);
        }
        
    }

    void TestPlayer::OnRender(Renderer renderer)
    {
        m_BatchRenderer.Begin();

        m_World.Render(renderer, m_Camera);

        for (auto& entity : m_LoadedEntities) {
            entity->render(m_BatchRenderer);
        }

        
        m_BatchRenderer.End();
        m_BatchRenderer.Render(renderer, m_Camera, *m_TileShader);
    }

    void TestPlayer::OnImGuiRender()
    {
        ImGui::Text("Application averaging %3.f ms/frame (%.2f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}