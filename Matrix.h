#pragma once

#include <cmath>
#include <utility>

template <typename T> class Matrix {
private:
    T* array;
    
    int index(int x, int y) const { return x + width * y; }

public:
    const int width, height;

    Matrix(int w, int h) : width(w), height(h), array(new T[w * h]) {}

    ~Matrix() { delete[] array; }

    void set(int x, int y, T value) { array[index(x, y)] = std::move(value); }

    template <typename... Args>
    void emplace(int x, int y, Args&&... args) {
        array[index(x, y)] = T(std::forward<Args>(args)...);
    }

    T& at(int x, int y) { return array[index(x, y)]; }

    T* getArray() const { return array; }
};