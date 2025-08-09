#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <vector>
#include <cmath>

struct Vec3 {
    float x, y, z;

    Vec3();
    Vec3(float x, float y, float z);

    Vec3 operator+(const Vec3 &other) const;
    Vec3 operator-(const Vec3 &other) const;
    Vec3 operator*(float scalar) const;
    Vec3 operator/(float scalar) const;
    bool operator==(const Vec3& other) const;

    float dot(const Vec3& other) const;
    Vec3 cross(const Vec3& other) const;
    float magnitude() const;
    Vec3 normalize() const;
    void print() const;

    static Vec3 determinant(const std::vector<Vec3>& A);
    static Vec3 dot(const std::vector<Vec3>& A, const std::vector<Vec3>& B);
};

// Hash function for Vec3 to use in unordered_map
namespace std {
    template <>
    struct hash<Vec3> {
        size_t operator()(const Vec3& v) const {
            return hash<float>()(v.x) ^ (hash<float>()(v.y) << 1) ^ (hash<float>()(v.z) << 2);
        }
    };
}

// Also define vec3 as alias for compatibility
using vec3 = Vec3;

#endif // VEC3_H
