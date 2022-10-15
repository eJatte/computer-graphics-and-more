#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define X_SIZE 1024
#define Y_SIZE 1024

float triangle_vertices[] = {
    -.5f, -.5f, 0.f,
    0.f, .5f, 0.f,
    .5f, -.5f, 0.f};

GLFWwindow* init(){
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(X_SIZE, Y_SIZE, "hello triangle", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0, 0, X_SIZE, Y_SIZE);
    return window;
}

int main()
{
    GLFWwindow* window = init();

    uint32_t v;
    glGenBuffers(1, &v);
    glBindBuffer(GL_ARRAY_BUFFER, v);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), &triangle_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}