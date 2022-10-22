#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader/Shader.h"
#include "Shader/Program.h"
#include "Geometry/Geometry.h"
#include "Input/Input.h"

#include <iostream>

#define X_SIZE 700
#define Y_SIZE 700

GLFWwindow *init() {
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(X_SIZE, Y_SIZE, "hello triangle", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glViewport(0, 0, X_SIZE, Y_SIZE);
    return window;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_RELEASE) {
        Input::get().addKeyboardEvent(key, false);
    } else if (action == GLFW_PRESS) {
        Input::get().addKeyboardEvent(key, true);
    }
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (action == GLFW_RELEASE) {
        Input::get().addKeyboardEvent(button + MOUSE_BUTTON_OFFSET, false);
    } else if (action == GLFW_PRESS) {
        Input::get().addKeyboardEvent(button + MOUSE_BUTTON_OFFSET, true);
    }
}

void cursor_position_callback(GLFWwindow *window, double x, double y) {
    Input::get().setMousePosition(glm::vec2(x, y));
}

int main() {
    GLFWwindow *window = init();

    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    Shader shader("../shaders/hello.vert", "../shaders/hello.frag");
    shader.compile();
    if (shader.hasErrors()) {
        shader.printErrors();
        return -1;
    }

    Program program = Program();
    program.link(shader);
    if (program.hasErrors()) {
        program.printErrors();
        return -1;
    }

    std::vector<glm::vec4> vertices_vbo;
    vertices_vbo.emplace_back(glm::vec4(-.75, -.5, 0, 1));
    vertices_vbo.emplace_back(glm::vec4(-.5, .5, 0, 1));
    vertices_vbo.emplace_back(glm::vec4(-.25, -.5, 0, 1));

    std::vector<glm::vec4> vertices_ebo;
    vertices_ebo.emplace_back(glm::vec4(.75, -.5, 0, 1));
    vertices_ebo.emplace_back(glm::vec4(.5, .5, 0, 1));
    vertices_ebo.emplace_back(glm::vec4(.25, -.5, 0, 1));

    std::vector<uint16_t> indices;
    indices.emplace_back(0);
    indices.emplace_back(1);
    indices.emplace_back(2);

    Geometry geometry_vbo(vertices_vbo);
    geometry_vbo.upload();

    Geometry geometry_ebo(vertices_ebo);
    geometry_ebo.setIndices(indices);
    geometry_ebo.upload();

    bool swap = false;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        Input::get().update();

        program.use();

        if (Input::get().keyUp(MOUSE_BUTTON_LEFT)) {
            swap = !swap;
        }

        if (swap) {
            geometry_vbo.render();
        } else {
            geometry_ebo.render();
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}