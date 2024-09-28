#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <memory>
#include "Vector2.h"
#include "Particle.h"
#include "Matrix.h"

class CollisionCell {
private:
    std::vector<Particle*> particles; //TODO: use idx instead?

public:
    CollisionCell() = default;

    void addParticle(Particle p) {
        particles.push_back(&p);
    }

    void clear() {
        particles.clear();
    }

    std::vector<Particle*> getParticles() const { return particles; }
};

class CollisionGrid {
private:
    Matrix<CollisionCell> grid;

public:
    const int width, height;

    CollisionGrid(int w, int h) : grid(Matrix<CollisionCell>(w, h)), width(w), height(h) {}

    void addParticle(Particle p, int x, int y) {
        grid.at(x, y).addParticle(p);
    }

    void clear() {
        for (int y = 0; y < grid.height; y++) {
            for (int x = 0; x < grid.width; x++) {
                grid.at(x, y).clear();
            }
        }
    }

    std::vector<Particle*> getParticles(int x, int y) const { 
        return grid.at(x, y).getParticles(); 
    }
};