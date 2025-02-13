#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <vector>
#include <cmath>

class Vec3 {
public:
    float x, y, z;

    // Constructors
    Vec3();
    Vec3(float x, float y, float z);

    // Operator Overloads
    Vec3 operator+(const Vec3& other) const;
    Vec3 operator-(const Vec3& other) const;
    Vec3 operator*(float scalar) const;
    Vec3 operator/(float scalar) const;
    bool operator==(const Vec3& other) const;
    
    // Utility functions
    float dot(const Vec3& other) const;
    Vec3 cross(const Vec3& other) const;
    float magnitude() const;
    Vec3 normalize() const;

    // Static functions for list operations (placeholders for QEF operations)
    static Vec3 determinant(const std::vector<Vec3>& A);
    static Vec3 dot(const std::vector<Vec3>& A, const std::vector<Vec3>& B);

    // Print function
    void print() const;
};

namespace std {
    template<> struct hash<Vec3> {
        size_t operator()(const Vec3& v) const {
            size_t h1 = std::hash<float>()(v.x);
            size_t h2 = std::hash<float>()(v.y);
            size_t h3 = std::hash<float>()(v.z);
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };
}

#endif // VEC3_H
