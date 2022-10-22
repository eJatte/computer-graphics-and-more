//
// Created by jatte on 2022-10-22.
//

#include "Input.h"

Input::Input() = default;

void Input::addKeyboardEvent(unsigned int key, bool pressed) {
    keyEvents.push({key, pressed});
}

void Input::addSpecialKeyEvent(unsigned int key, bool pressed) {
    addKeyboardEvent(key + GLFW_KEY_LAST + 1 + 8, pressed);
}

void Input::addMouseButtonEvent(unsigned int key, bool pressed) {
    addKeyboardEvent(key + GLFW_KEY_LAST + 1, pressed);
}


void Input::update() {
    for (auto &key: keys) {
        if (key == DOWN) {
            key = PRESSED;
        } else if (key == UP) {
            key = RELEASED;
        }
    }

    while (!keyEvents.empty()) {
        KeyEvent event = keyEvents.front();

        KeyState &keyState = keys[event.key];

        if (event.pressed && keyState == RELEASED) {
            keyState = DOWN;
        } else if (!event.pressed && keyState == PRESSED) {
            keyState = UP;
        }

        keyEvents.pop();
    }

    if (!newMousePos)
        mouse_delta = glm::vec2();

    newMousePos = false;
}

bool Input::key(unsigned int key) {
    return keys[key] == PRESSED || keys[key] == DOWN;
}

bool Input::keyUp(unsigned int key) {
    return keys[key] == UP;
}

bool Input::keyDown(unsigned int key) {
    return keys[key] == DOWN;
}

void Input::setMousePosition(glm::vec2 position) {
    newMousePos = true;
    mouse_delta = position - mouse_position;
    mouse_position = position;
}

glm::vec2 Input::mousePosition() {
    return mouse_position;
}

glm::vec2 Input::mouseDelta() {
    return mouse_delta;
}

const char *Input::key_name(unsigned int key) {
    return glfwGetKeyName(key, 0);
}
