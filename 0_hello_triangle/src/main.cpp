#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader/Shader.h"
#include "Shader/Program.h"

#include <iostream>

#define X_SIZE 700
#define Y_SIZE 700

float triangle_vertices[] = {
        -.5f, -.5f, 0.f,
        0.f, .5f, 0.f,
        .5f, -.5f, 0.f};

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

    uint32_t v;
    glGenBuffers(1, &v);
    glBindBuffer(GL_ARRAY_BUFFER, v);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), &triangle_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}