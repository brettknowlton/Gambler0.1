#include "TestRenderWorld.h"
#include "GLMacros.h"
#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


namespace test{

        TestRenderWorld::TestRenderWorld ()
        :m_Camera(512, 288), m_World(1, 1), m_Translation(0,0,0)
        {
            m_Camera.SetPosition(0,0);
        
        }

        TestRenderWorld::~TestRenderWorld ()
        {
        }
    
        void TestRenderWorld::OnUpdate(float deltaTime)
        {
            //tick or update
            m_World.Tick(0.0f);
        }
    
        void TestRenderWorld::OnRender(Renderer renderer)
        {
            m_World.Render(renderer, m_Camera);
        }
    
        void TestRenderWorld::OnImGuiRender()
        {
            ImGui::SliderFloat2("Translation", &m_Translation.x, 0.0f, 960.0f);
            ImGui::Text("Application averaging %3.f ms/frame (%.2f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
}