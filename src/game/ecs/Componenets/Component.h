#pragma once

namespace component {
class Component {
public:
    virtual ~Component() {};

    virtual void update(float dt) = 0;

    virtual void render(BatchRenderer& bRenderer) = 0;
};
}