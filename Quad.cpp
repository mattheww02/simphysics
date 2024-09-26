#include <GLFW/glfw3.h>
#include "Quad.h"
#include "PhysicsObject.h"

Quad::Quad(
    float x, float y, 
    float r, float g, float b, 
    float xVelocity, float yVelocity,
    bool hasGravity,
    float w, float h
) : PhysicsObject(x, y, r, g, b, xVelocity, yVelocity, hasGravity), w(w), h(h) {}

void Quad::render() {
    glColor3f(r, g, b);  // Brown color for the floor

    glBegin(GL_QUADS);
        glVertex2f(x, y);  // Bottom-left (in front)
        glVertex2f(x + w, y);  // Bottom-right (in front)
        glVertex2f(x + w, y + h);  // Top-right (in back)
        glVertex2f(x, y + h);  // Top-left (in back)
    glEnd();
}
