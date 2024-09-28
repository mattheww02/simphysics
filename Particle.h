#pragma once

#include <utility>
#include <tuple>
#include <GLFW/glfw3.h>
#include "Vector2.h"

class Particle {
public:

    Vector2 position = Vector2(0.0f, 0.0f);
    Vector2 prev_position = Vector2(0.0f, 0.0f);
    Vector2 acceleration = Vector2(0.0f, 0.0f);
    float color[3] = {1.0f, 1.0f, 1.0f};

    Particle() = default; // default constructor

    Particle( // instantiate with position only
        float p_x, float p_y
    ) : position(Vector2(p_x, p_y)) {}

    Particle( // instantiate with position and previous position
        float p_x, float p_y,
        float l_x, float l_y
    ) : position(Vector2(p_x, p_y)), prev_position(Vector2(l_x, l_y)) {}

    void update(float dt) { // update position and velocity
        Vector2 position_dist = position - prev_position;

        const float VELOCITY_DAMPING = 1e4f; // arbitrary, approximating air friction

        const Vector2 new_position = position + position_dist + (acceleration - position_dist * VELOCITY_DAMPING) * (dt * dt);
        prev_position = position;
        position = new_position;
        acceleration = Vector2(0.0f, 0.0f);
    }

    void setPosition(Vector2 p) {
        position = p;
    }

    void accelerate(Vector2 v) {
        prev_position -= v;
    }

    void move(Vector2 v) {
        position += v;
    }

    void stop() {
        prev_position = position;
    }

    void render() { // render object with OpenGL
        glPointSize(2.0f);
        glColor3f(color[0], color[1], color[2]);
        glBegin(GL_POINTS);
        glVertex2f(position.x, position.y);
        glEnd();
    }
};