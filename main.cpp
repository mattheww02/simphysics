#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <memory>
#include <stdlib.h>
#include "Particle.h"
#include "Physics.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
    const int window_width = 800;
    const int window_height = 600;

    // init GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW init failed!" << std::endl;
        return -1;
    }
    // create an OpenGL window
    GLFWwindow* window = glfwCreateWindow(window_width, window_height, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "Window init failed!" << std::endl;
        glfwTerminate();
        return -1;
    }
    const float zoom = 2.0f;
    const Vector2 translate = Vector2(500.0f, 0.5f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Physics physics = Physics(Vector2(1.2f, 0.8f));

    float dt = 0.0f;
    float prev_frame = 0.0f;
    
    // main render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // render background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // calculate delta time
        const float cur_frame = glfwGetTime();
        dt = cur_frame - prev_frame;
        prev_frame = cur_frame; //TODO: pass prev_frame instead of dt to increase accuracy

        // update and render particles
        physics.update(1e-1f);
        physics.render();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
