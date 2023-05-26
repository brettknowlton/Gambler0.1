#pragma once
#include <vector>
#include <memory>
#include "game\ecs\Componenets\Component.h"

class Entity{
private:
    std::vector<std::shared_ptr<component::Component>> components;
public:

    Entity();
    ~Entity();

    void addComponent(std::shared_ptr<component::Component> component) {
        components.push_back(component);
    }

    void update(float dt) {
        for (auto& component : components) {
            component->update(dt);
        }
    }

    void render(BatchRenderer& renderer) {
        for (auto& component : components) {
            component->render(renderer);
        }
    }

    template<typename T>
    std::shared_ptr<T> getComponent() {
        for (auto& component : components) {
            if (std::dynamic_pointer_cast<T>(component)) {
                return std::dynamic_pointer_cast<T>(component);
            }
        }
        return nullptr;
    }

};