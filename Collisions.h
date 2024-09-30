#pragma once

#include <vector>
#include "Particle.h"
#include "Matrix.h"
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <atomic>


class CollisionCell {
private:
    std::vector<size_t> particle_indices;
    std::mutex cell_mutex;

public:
    CollisionCell() = default; // default constructor

    CollisionCell(const CollisionCell& other) // copy constructor
        : particle_indices(other.particle_indices) {
    }

    CollisionCell(CollisionCell&& other) noexcept { // move constructor
        this->particle_indices = std::move(other.particle_indices);
    }

    // Copy assignment operator
    CollisionCell& operator=(const CollisionCell& other) {
        if (this != &other) { // Self-assignment check
            particle_indices = other.particle_indices; // Copy the particle indices
        }
        return *this; // Return *this to allow chaining
    }

    // Move assignment operator
    CollisionCell& operator=(CollisionCell&& other) noexcept {
        if (this != &other) { // Self-assignment check
            particle_indices = std::move(other.particle_indices); // Move the particle indices
        }
        return *this; // Return *this to allow chaining
    }

    void addParticle(size_t idx) {
        std::lock_guard<std::mutex> lock(cell_mutex);
        particle_indices.push_back(idx);
    }

    void clear() {
        std::lock_guard<std::mutex> lock(cell_mutex);
        particle_indices.clear();
    }

    std::vector<size_t> getParticleIndices() {
        std::lock_guard<std::mutex> lock(cell_mutex);
        return particle_indices;
    }
};

class CollisionGrid {
private:
    Matrix<CollisionCell> grid;

public:
    std::vector<Particle> particles;

    const int width, height;

    CollisionGrid(int w, int h) : grid(Matrix<CollisionCell>(w, h)), width(w), height(h) {
        for (int y = 0; y < grid.height; y++) {
            for (int x = 0; x < grid.width; x++) {
                grid.emplace(x, y, CollisionCell{});
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

    std::vector<size_t> getParticleIndices(int x, int y) {
        return grid.at(x, y).getParticleIndices();
    }

    Particle& getParticle(size_t idx) {
        return particles[idx]; // Access particle by its index
    }

    // const Particle& getParticle(size_t idx) const {
    //     return particles[idx];
    // }
};
