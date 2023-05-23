#pragma once

namespace component {
class Component {
public:
    virtual ~Component() = default;

    virtual void update(float dt) = 0;

    virtual void render(Renderer renderer) = 0;
};
}