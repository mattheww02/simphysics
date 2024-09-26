#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <memory>
#include "Particle.h"
#include "Quad.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main() {
    // init GLFW
    if (!glfwInit()) {
        std::cerr << "GLFW init failed!" << std::endl;
        return -1;
    }
    // create an OpenGL window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
    if (!window) {
        std::cerr << "Window init failed!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // set initial conditions
    std::vector<std::unique_ptr<PhysicsObject>> physicsObjects;
    physicsObjects.push_back(std::make_unique<Particle>(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0001f, true, 10.0f));
    physicsObjects.push_back(std::make_unique<Particle>(0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.00015f, true, 10.0f));
    physicsObjects.push_back(std::make_unique<Quad>(-2.0f, -1.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, false, 4.0f, 0.2f));

    // main render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // render background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render particle
        for (auto& obj: physicsObjects){
            obj -> render();
            obj -> update();
        }

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
