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

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set up projection (zoom and translate)
    const float zoom = 1.0f; // Increase this value to zoom out (larger view)
    const Vector2 translate(0.0f, 0.0f); // Adjust this for translation if needed

    glMatrixMode(GL_PROJECTION); // Switch to projection mode
    glLoadIdentity();            // Reset any existing projection
    glOrtho(
        -window_width / 2.0f * zoom + translate.x, 
        window_width / 2.0f * zoom + translate.x, 
        -window_height / 2.0f * zoom + translate.y, 
        window_height / 2.0f * zoom + translate.y, 
        -1.0f, 1.0f
    ); // Apply zoom and translation
    glMatrixMode(GL_MODELVIEW);  // Switch back to model-view mode
    glLoadIdentity();            // Reset the model-view matrix

    Physics physics = Physics(Vector2(200.0f, 150.0f), 6);

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
        prev_frame = cur_frame; // TODO: pass prev_frame instead of dt to increase accuracy

        // update and render particles
        physics.update(0.1f);
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
