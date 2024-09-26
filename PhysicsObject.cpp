#include "Physics.h"
#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(
    float x, float y,
    float r, float g, float b, 
    float xVelocity, float yVelocity,
    bool hasGravity
) : x(x), y(y), r(r), g(g), b(b), xVelocity(xVelocity), yVelocity(yVelocity), hasGravity(hasGravity) {}

void PhysicsObject::update(){
    x += xVelocity;
    y += yVelocity;

    if (hasGravity) yVelocity -= Physics::GRAVITY;
    
    xVelocity *= (1 - Physics::AIR_RESISTANCE);
    yVelocity *= (1 - Physics::AIR_RESISTANCE);
}

void PhysicsObject::render() {}