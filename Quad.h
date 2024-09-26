#ifndef QUAD_H
#define QUAD_H

#include "PhysicsObject.h"

class Quad : public PhysicsObject {
public:
    float w, h; // size

    Quad(
        float x, float y, 
        float r, float g, float b, 
        float xVelocity, float yVelocity,
        bool hasGravity,
        float w, float h
    );

    void render() override;
};

#endif