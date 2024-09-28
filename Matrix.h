#pragma once

#include <cmath>

template <typename T> class Matrix {
private:
    T* array;
    
    int index(int x, int y) const { return x + width * y; }

public:
    const int width, height;

    Matrix(int w, int h) : width(w), height(h), array(new T[w * h]) {}

    ~Matrix() { delete[] array; }

    T at(int x, int y) const { return array[index(x, y)]; }

    T* getArray() const { return array; }
};