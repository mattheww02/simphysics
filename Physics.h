#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <memory>
#include "Vector2.h"
#include "Particle.h"

class Physics {
    const Vector2 GRAVITY = Vector2(0.0f, -9.81f);
    const Vector2 container_size;
    const float AIR_RESISTANCE = 0.1f;
    const float FRICTION = 0.001f;
    const float BOUNCE_COEF = 0.1f;

    std::vector<Particle> particles;

 public: 

    Physics(Vector2 size) : container_size(size) {
        for (int i = 0; i < 500; i++) {
            particles.push_back(Particle(
                getRandomBetween(0.01f, container_size.x - 0.01f), 
                getRandomBetween(0.01f, container_size.y - 0.01f)
            ));
        }
    };

    void update(float dt) {
        const float margin = 1.4e-2f;
        for (auto& obj : particles) {
            obj.update(dt);
            obj.acceleration += GRAVITY;

            if (obj.position.x > container_size.x - margin) {
                    obj.position.x = container_size.x - margin;
            } else if (obj.position.x < margin) {
                obj.position.x = margin;
            }
            if (obj.position.y > container_size.y - margin) {
                obj.position.y = container_size.y - margin;
            } else if (obj.position.y < margin) {
                obj.position.y = margin;
            }

            for (auto& obj2 : particles) {
                if (&obj != &obj2){
                    handleCollision(obj, obj2);
                }
            }
        }
    }

    void render() {
        for (auto& obj: particles) {
            obj.render();
        }
    }

    float getRandomBetween(float min, float max){
        return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
    }

    void handleCollision(Particle& obj1, Particle& obj2) {
        const float r = 7e-3f;
        const float eps = 7e-5f;

        const float dist = obj1.position.getDistance(obj2.position);
        
        if (dist < r && dist > eps){
            const float delta  = 0.5f * (r - dist);
            
            const Vector2 disp = ((obj1.position - obj2.position) / dist) * delta;
            obj1.position += disp;
            obj2.position -= disp;
        }
    }
};
