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

uint32_t indices[] = {0, 1, 2};

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

    program.use();
    int32_t m_attribute_v_coord = program.getAttribLocation("v_coord");

    uint32_t VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(m_attribute_v_coord);
    glVertexAttribPointer(m_attribute_v_coord, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        program.use();

        glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}