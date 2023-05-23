#pragma once
#include <vector>
#include <memory>
#include "game\ecs\Componenets\Component.h"


namespace game{

class Entity {
private:
    std::vector<std::unique_ptr<Component>> components;

public:
    void addComponent(Component* component) {
        components.push_back(std::unique_ptr<Component>(component));
    }

    void update() {
        for (auto& component : components) {
            component->update();
        }
    }

    void render() {
        for (auto& component : components) {
            component->render();
        }
    }
};
}