#pragma once
#include "game\ecs\Componenets\Component.h"
#include "game\ecs\Entity.h"

namespace game{
    class TransformComponent : public Component {
    public:
        Transform(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
            const glm::vec3& rotation = glm::vec3(0.0f, 0.0f, 0.0f),
            const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f))
            : m_Position(position), m_Rotation(rotation), m_Scale(scale) {}
        ~Transform() = default;

        void update() override {
            //todo
        }

    private:
        glm::vec3 m_Position;
        glm::vec3 m_Rotation;
        glm::vec3 m_Scale;
    };