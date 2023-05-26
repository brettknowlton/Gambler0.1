#pragma once
#include "Component.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace component{
    class Transform : public Component {
    public:
        Transform(  glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
                    glm::vec3 rotation= glm::vec3(0.0f, 0.0f, 0.0f), 
                    glm::vec3 scale=  glm::vec3(1.0f, 1.0f, 1.0f));

        ~Transform();

        void update(float dt) override;
        void render(BatchRenderer& renderer);

        glm::vec3 getPosition() const { return m_Position; }

    private:
        glm::vec3 m_Position;
        glm::vec3 m_Rotation;
        glm::vec3 m_Scale;

        std::string m_Name = "Transform";
    };
}