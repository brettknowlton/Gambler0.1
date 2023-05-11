#pragma once
#include "Test.h"
#include "GLMacros.h"

#include "game/Camera.h"
#include "game/World.h"
#include "game/Player.h"

#include "renderer/BatchRenderer.h"
#include <memory>

#include "glm/glm.hpp"


namespace test{

    class TestPlayer : public Test
    {
    public:
        TestPlayer ();
        ~TestPlayer ();

        void OnUpdate(float deltaTime) override;
        void OnRender(Renderer renderer) override;
        void OnImGuiRender() override;

    private:
        game::Camera m_Camera;
        game::World m_World;
        game::Player m_Player;

        Renderer renderer;

        glm::vec3 m_Translation;

    };
}