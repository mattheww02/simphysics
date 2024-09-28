#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <memory>
#include <stdlib.h>
#include "PhysicsObject.h"
#include "Physics.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
float getRandomBetween(float min, float max);

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
    std::vector<PhysicsObject> physics_objects;
    physics_objects.push_back(PhysicsObject(0.0f, 0.0f, 0.5f, 0.5f));
    physics_objects.push_back(PhysicsObject(0.2f, 0.0f, 0.5f, 0.7f));
    // for (int i = 0; i < 200; i++){
    //     physics_objects.push_back(PhysicsObject(
    //         getRandomBetween(-0.3f, 0.3f), getRandomBetween(-0.0f, 0.5f), 
    //         getRandomBetween(-0.5f, 0.5f), getRandomBetween(-0.5f, 0.5f)
    //     ));
    // }
    
    
    // main render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // render background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render particle
        for (auto& obj: physics_objects) {
            obj.render();
            obj.update(5e-4f);

            if (obj.p_y <= -0.1f) {
                obj.setVelocity(obj.v_x * (1 - Physics::FRICTION), -obj.v_y * (1 - Physics::FRICTION));
            }
            if (obj.p_x <= -0.4f || obj.p_x >= 0.4f) {
                obj.setVelocity(-obj.v_x * (1 - Physics::FRICTION), obj.v_y * (1 - Physics::FRICTION));
            }
            obj.accelerate(0.0f, -Physics::GRAVITY);

            for (auto& obj2: physics_objects) {
                if (abs(obj.p_x - obj2.p_x) < 4e-3f && 
                    abs(obj.p_y - obj2.p_y) < 4e-3f &&
                    &obj != &obj2) {
                        obj.setVelocity(-obj.v_x, -obj.v_y);
                }
            }

            if (physics_objects.size() < 200 && rand() % 10000 == 1) {
                physics_objects.push_back(PhysicsObject(
                    getRandomBetween(-0.3f, 0.3f), getRandomBetween(-0.0f, 0.5f), 
                    getRandomBetween(-0.5f, 0.5f), getRandomBetween(-0.5f, 0.5f)
                ));
            }
        }

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

float getRandomBetween(float min, float max){
    return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
