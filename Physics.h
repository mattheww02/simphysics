#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <memory>
#include "Vector2.h"
#include "Particle.h"
#include "Collisions.h"

class Physics {
    const Vector2 GRAVITY = Vector2(0.0f, -9.81f);
    const Vector2 container_size;
    const int sub_steps = 8;

    std::vector<Particle> particles;
    CollisionGrid collision_grid = CollisionGrid(8, 8);

 public: 

    Physics(Vector2 size) : container_size(size) {
        for (int i = 0; i < 500; i++) {
            particles.push_back(Particle(
                getRandomBetween(0.01f, container_size.x - 0.01f), 
                getRandomBetween(0.01f, container_size.y - 0.01f)
            ));
        }
        srand(time(0));
    };

    void update(float dt) {
        const float sub_dt = dt / static_cast<float>(sub_steps);
        for (int i = 0; i < sub_steps; i++) {
            handleCollisions();
            handleMotion(sub_dt);
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

    void handleMotion(float dt) {
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
        }
    }

    void handleCollisions() {
        for (auto& p : particles) {
            const int x = static_cast<int>(floor(p.position.x * collision_grid.width / container_size.x));
            const int y = static_cast<int>(floor(p.position.y * collision_grid.height / container_size.y));
            collision_grid.addParticle(p, x, y);
        }
        
        for (int y = 0; y < collision_grid.height; y++) {
            for (int x = 0; x < collision_grid.width; x++) {
                std::vector<Particle*> ps = collision_grid.getParticles(x, y);
                for (size_t i = 0; i < ps.size(); ++i) {
                    for (size_t j = i + 1; j < ps.size(); ++j) {
                        handleCollision(*ps[i], *ps[j]);
                        std::cout << "AAAAAAAAAA\n"; 
                    }
                }
                
            }
        }

        
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
