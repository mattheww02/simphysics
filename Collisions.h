#pragma once

#include <vector>
#include "Particle.h"
#include "Matrix.h"
#include <iostream>

class CollisionCell {
private:
    std::vector<size_t> particle_indices; // Use indices instead of pointers

public:
    CollisionCell() = default;

    void addParticle(size_t idx) {
        particle_indices.push_back(idx);
        //std::cout << "Added particle " << idx << ": " << particle_indices[0] << std::endl;
    }

    void clear() {
        particle_indices.clear();
    }

    std::vector<size_t>& getParticleIndices() {
        return particle_indices;
    }
};

class CollisionGrid {
private:
    Matrix<CollisionCell> grid;

public:
    std::vector<Particle> particles; // Global particle list

    const int width, height;

    CollisionGrid(int w, int h) : grid(Matrix<CollisionCell>(w, h)), width(w), height(h) {
        for (int y = 0; y < grid.height; y++) {
            for (int x = 0; x < grid.width; x++) {
                grid.set(x, y, CollisionCell());
            }
        }
    }

    void addParticle(size_t idx, int x, int y) {
        grid.at(x, y).addParticle(idx);
    }

    void clear() {
        for (int y = 0; y < grid.height; y++) {
            for (int x = 0; x < grid.width; x++) {
                grid.at(x, y).clear();
            }
        }
    }

    std::vector<size_t>& getParticleIndices(int x, int y) {
        return grid.at(x, y).getParticleIndices();
    }

    Particle& getParticle(size_t idx) {
        return particles[idx]; // Access particle by its index
    }

    const Particle& getParticle(size_t idx) const {
        return particles[idx];
    }
};
