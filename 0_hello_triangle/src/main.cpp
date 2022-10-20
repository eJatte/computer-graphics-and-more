#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader/Shader.h"
#include "Shader/Program.h"
#include "Geometry/Geometry.h"

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

int main() {
    GLFWwindow *window = init();

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

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();

        geometry_vbo.render();
        geometry_ebo.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}