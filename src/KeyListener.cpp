#pragma once
#include <array>

class KeyListener {
public:
    static KeyListener& GetInstance() {
        static KeyListener instance;
        return instance;
    }

    void SetKeyState(int key, int action) {
        m_Keys[key] = action;
    }

    int GetKeyState(int key) {
        return m_Keys[key];
    }

private:
    KeyListener() {}
    ~KeyListener() {}

    std::array<int, GLFW_KEY_LAST + 1> m_Keys;
};
#define KEYLOOKUP(key) KeyListener::GetInstance().GetKeyState(key)
