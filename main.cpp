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
void handleCollision(PhysicsObject& obj1, PhysicsObject& obj2);

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
    
    float dt = 0.0f;
    float prev_frame = 0.0f;
    
    // main render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // render background
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render particle
        for (auto& obj: physics_objects) {
            const float cur_frame = glfwGetTime();
            dt = cur_frame - prev_frame;
            prev_frame = cur_frame;

            obj.render();
            obj.update(dt * 100);

            if (obj.p_y <= -0.1f) {
                obj.setVelocity(obj.v_x * (1 - Physics::FRICTION), -obj.v_y * Physics::BOUNCE_COEF);
                if (obj.p_y < -0.1f){
                    obj.p_y = -0.1f;
                }
            }
            if (obj.p_x <= -0.4f || obj.p_x >= 0.4f) {
                obj.setVelocity(-obj.v_x * Physics::BOUNCE_COEF, obj.v_y * (1 - Physics::FRICTION));
            }
            
            for (auto& obj2: physics_objects) {
                if (&obj != &obj2) {
                    handleCollision(obj, obj2);
                }
                else{
                    obj.accelerate(0.0f, -Physics::GRAVITY);
                }
            }

            if (physics_objects.size() < 800 && rand() % 1000 == 1) {
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

void handleCollision(PhysicsObject& obj1, PhysicsObject& obj2) {
    const float r = 7e-3f;

    const float eps = 5e-8f;
    const float dx = obj1.p_x - obj2.p_x;
    const float dy = obj1.p_y - obj2.p_y;
    const float dist2 = dx * dx + dy * dy;
    
    if (dist2 < r * r && dist2 > eps){
        const float dist = sqrt(dist2);
        const float delta  = 0.5f * (r - dist);
        
        const float vx = (dx / dist) * delta;
        const float vy = (dy / dist) * delta;
        obj1.p_x += vx;
        obj1.p_y += vy;
        obj2.p_x -= vx;
        obj2.p_y -= vy;
    }
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
