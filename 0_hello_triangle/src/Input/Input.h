//
// Created by jatte on 2022-10-22.
//

#ifndef ANDROMEDA_INPUT_H
#define ANDROMEDA_INPUT_H

#include <queue>
#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>
#include "KeyCodes.h"

class Input {
public:
    static Input &get() {
        static Input instance;
        return instance;
    }

    Input(Input const &) = delete;

    void operator=(Input const &) = delete;

    const char *key_name(unsigned int key);

    void addKeyboardEvent(unsigned int key, bool pressed);

    void addSpecialKeyEvent(unsigned int key, bool pressed);

    void addMouseButtonEvent(unsigned int key, bool pressed);

    void setMousePosition(glm::vec2 position);

    glm::vec2 mousePosition();

    glm::vec2 mouseDelta();

    bool key(unsigned int key);

    bool keyUp(unsigned int key);

    bool keyDown(unsigned int key);

    void update();

private:
    Input();

    enum KeyState {
        RELEASED, DOWN, PRESSED, UP
    };

    struct KeyEvent {
        unsigned int key;
        bool pressed;
    };

    KeyState keys[KEY_LAST]{RELEASED};

    std::queue<KeyEvent> keyEvents;

    glm::vec2 mouse_position = glm::vec2(0);
    glm::vec2 mouse_delta = glm::vec2(0);

    bool newMousePos;
};


#endif //ANDROMEDA_INPUT_H
