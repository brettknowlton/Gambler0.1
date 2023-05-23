#pragma once
#include <vector>
#include <memory>
#include "game\ecs\Componenets\Component.h"

class Entity{
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

    void render(BatchRenderer renderer) {
        for (auto& component : components) {
            component->render(renderer);
        }
    }

private:
    std::vector<std::shared_ptr<component::Component>> components;

};