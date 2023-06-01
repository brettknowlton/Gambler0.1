#pragma once
#include "Test.h"
#include "GLMacros.h"
#include "game/ecs/Entity.h"

#include "renderer/BatchRenderer.h"
#include <memory>


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
        BatchRenderer m_BatchRenderer;

        game::Camera m_Camera;
        game::World m_World;
        Entity m_Player = Entity();

        Renderer renderer;

        std::vector<std::shared_ptr<Entity>> m_LoadedEntities;
        std::shared_ptr<Shader> m_TileShader;
    };
}