#pragma once
#include "Test.h"

#include "renderer/VertexBuffer.h"
#include "renderer/IndexBuffer.h"
#include "renderer/VertexBufferLayout.h"
#include "renderer/Texture.h"

#include <memory>


namespace test{

    class TestBatchedRendering : public Test
    {
    public:
        TestBatchedRendering ();
        ~TestBatchedRendering ();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IB;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;

        glm::mat4 m_Proj, m_View;

        glm::vec3 m_Translation;


    };
}