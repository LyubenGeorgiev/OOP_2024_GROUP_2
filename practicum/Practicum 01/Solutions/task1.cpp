#include <iostream>
#include <cmath>


const double EPSILON = 1.0/(1LL<<30);

struct Vector {
    int x, y, z;
};

Vector add(const Vector &lhs, const Vector &rhs) {
    return Vector{lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
}

void printVector(const Vector &vec) {
    std::cout << "Vector{" << vec.x << ", " << vec.y << ", " << vec.z << '}';
}

// Unhandled division by zero !!!
bool linearlyDependent(const Vector &lhs, const Vector &rhs) {
    double coefX = (double)lhs.x / rhs.x;
    double coefY = (double)lhs.y / rhs.y;
    double coefZ = (double)lhs.z / rhs.z;

    return fabsf64(coefX - coefY) < EPSILON && fabsf64(coefX - coefZ) < EPSILON;
}