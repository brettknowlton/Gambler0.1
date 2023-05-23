#pragma once

namespace game {
class Component {
public:
    virtual ~Component() = default;

    virtual void update() = 0;

    virtual void render() = 0;
};
}