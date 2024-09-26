#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H

class PhysicsObject {
public:
    float x, y;     // position
    float r, g, b;  // color
    float xVelocity, yVelocity; // velocity
    bool hasGravity; // whether gravity is enabled for the object

    PhysicsObject(
        float x, float y, 
        float r, float g, float b, 
        float xVelocity, float yVelocity,
        bool hasGravity
    );

    void update();

    virtual void render();
};

#endif