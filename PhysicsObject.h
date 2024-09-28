#pragma once

#include <GLFW/glfw3.h>
#include "Physics.h"

class PhysicsObject {
public:

    float p_x = 0.0f, p_y = 0.0f; // position
    float v_x = 0.0f, v_y = 0.0f; // velocity
    float a_x = 0.0f, a_y = 0.0f; // acceleration
    float r = 1.0f, g = 1.0f, b = 1.0f;  // color

    PhysicsObject() = default; // default constructor

    PhysicsObject( // instantiate with position only
        float p_x, float p_y
    ) : p_x(p_x), p_y(p_y) {}

    PhysicsObject( // instantiate with position and velocity
        float p_x, float p_y,
        float v_x, float v_y
    ) : p_x(p_x), p_y(p_y), v_x(v_x), v_y(v_y) {}

    PhysicsObject( // instantiate with position, velocity and acceleration
        float p_x, float p_y,
        float v_x, float v_y,
        float a_x, float a_y
    ) : p_x(p_x), p_y(p_y), v_x(v_x), v_y(v_y), a_x(a_x), a_y(a_y) {}

    void update(float dt) { // update position and velocity
        p_x += dt * v_x; // apply velocity
        p_y += dt * v_y;

        v_x += dt * a_x; // apply acceleration
        v_y += dt * a_y;

        v_x *= (1 - dt * Physics::AIR_RESISTANCE); // apply air resistance
        v_y *= (1 - dt * Physics::AIR_RESISTANCE);

        a_x = 0.0f; // reset acceleration
        a_y = 0.0f;
    }

    void setPosition(float x, float y) {
        p_x = x;
        p_y = y;
    }

    void accelerate(float x, float y) {
        a_x += x;
        a_y += y;
    }

    void setVelocity(float x, float y) {
        v_x = x;
        v_y = y;
    }

    void render() { // render object with OpenGL
        glPointSize(2.0f);
        glColor3f(r, g, b);
        glBegin(GL_POINTS);
        glVertex2f(p_x, p_y);
        glEnd();
    }

private:

  

};