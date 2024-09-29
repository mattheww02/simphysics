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
    float time_since_last_particle = 0.0f;
    float time_elapsed = 0.0f;

    CollisionGrid collision_grid = CollisionGrid(16, 8);

 public: 

    Physics(Vector2 size) : container_size(size) {
        srand(time(0));
    };

    void update(float dt) {
        time_elapsed += dt;
        if (time_elapsed < 2500.0f) return;
        time_since_last_particle += dt;
        if (time_since_last_particle > 0.05f && collision_grid.particles.size() < 1500) {
            collision_grid.particles.push_back(Particle(
                getRandomBetween(0.04f, 0.05f), 
                getRandomBetween(container_size.y - 0.02f, container_size.y - 0.01f),
                -20.0f, container_size.y - 0.02f,
                static_cast<float>(abs(sin(time_elapsed / 50))),
                static_cast<float>(abs(sin(time_elapsed / 50 + 1.0f))),
                static_cast<float>(abs(sin(time_elapsed / 50 + 2.0f)))
            ));
            time_since_last_particle = 0.0f;
        }

        const float sub_dt = dt / static_cast<float>(sub_steps);
        for (int i = 0; i < sub_steps; i++) {
            handleCollisions();
            handleMotion(sub_dt);
        }
    }

    void render() {
        for (auto& obj: collision_grid.particles) {
            obj.render();
        }
    }

    float getRandomBetween(float min, float max){
        return min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max-min)));
    }

    void handleMotion(float dt) {
        const float margin = 1.4e-2f;
        for (auto& obj : collision_grid.particles) {
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
        collision_grid.clear();
        for (int i = 0; i < collision_grid.particles.size(); i++) {
            const int x = static_cast<int>(floor(collision_grid.particles[i].position.x * collision_grid.width / container_size.x));
            const int y = static_cast<int>(floor(collision_grid.particles[i].position.y * collision_grid.height / container_size.y));
            collision_grid.addParticle(i, x, y);
        }
        
        for (int y = 0; y < collision_grid.height; y++) {
            for (int x = 0; x < collision_grid.width; x++) {
                // Check current cell and neighboring cells
                for (int dy = -1; dy <= 1; dy++) {
                    for (int dx = -1; dx <= 1; dx++) {
                        int neighbor_x = x + dx;
                        int neighbor_y = y + dy;

                        // Ensure we stay within grid bounds
                        if (neighbor_x >= 0 && neighbor_x < collision_grid.width &&
                            neighbor_y >= 0 && neighbor_y < collision_grid.height) {
                            
                            std::vector<size_t> indices = collision_grid.getParticleIndices(neighbor_x, neighbor_y);
                            for (size_t idx1 : indices) {
                                Particle& p1 = collision_grid.getParticle(idx1);
                                for (size_t idx2 : indices) {
                                    if (idx1 > idx2) {
                                        Particle& p2 = collision_grid.getParticle(idx2);
                                        handleCollision(p1, p2);
                                    }
                                }
                            }
                        }
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
