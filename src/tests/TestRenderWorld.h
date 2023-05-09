#pragma once
#include "Test.h"
#include "GLMacros.h"
#include "Camera.h"
#include "World.h"

#include "renderer/BatchRenderer.h"
#include <memory>

#include "glm/glm.hpp"


namespace test{

    class TestRenderWorld : public Test
    {
    public:
        TestRenderWorld ();
        ~TestRenderWorld ();

        void OnUpdate(float deltaTime) override;
        void OnRender(Renderer renderer) override;
        void OnImGuiRender() override;

    private:
        game::Camera m_Camera;
        game::World m_World;
        Renderer renderer;

        glm::vec3 m_Translation;

    };
}