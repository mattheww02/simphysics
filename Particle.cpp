#include <GLFW/glfw3.h>
#include "Particle.h"
#include "PhysicsObject.h"

Particle::Particle(
    float x, float y, 
    float r, float g, float b, 
    float xVelocity, float yVelocity,
    bool hasGravity,
    float size
) : PhysicsObject(x, y, r, g, b, xVelocity, yVelocity, hasGravity), size(size) {}

void Particle::render() {
    glPointSize(size);
    glColor3f(r, g, b);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}
