#pragma once
#include "game/ecs/Componenets/Component.h"
#include "game/ecs/Entity.h"
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"

namespace component{
    class Transform : public Component {
    public:
        Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
        ~Transform();

        void update(float dt) override;
        void render(BatchRenderer renderer) override;

    private:
        glm::vec3 m_Position;
        glm::vec3 m_Rotation;
        glm::vec3 m_Scale;
    };
}