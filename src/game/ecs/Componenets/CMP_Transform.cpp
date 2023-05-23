#include "CMP_Transform.h"

namespace component {

    Transform::Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) 
        : m_Position(position), m_Rotation(rotation), m_Scale(scale) {
    }

    Transform::~Transform() {
        //todo
    }

    void Transform::update(float dt) {
        //todo
        std::cout << "Transform::update\n";
    }

    void Transform::render(BatchRenderer& renderer) override{
        //todo
        std::cout << "Transform::render\n";
    }
}