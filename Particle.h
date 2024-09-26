#ifndef PARTICLE_H
#define PARTICLE_H

#include "PhysicsObject.h"

class Particle : public PhysicsObject {
public:
    float size; // particle size

    Particle(
        float x, float y, 
        float r, float g, float b, 
        float xVelocity, float yVelocity,
        bool hasGravity,
        float size
    );

    void render() override;
};

#endif
