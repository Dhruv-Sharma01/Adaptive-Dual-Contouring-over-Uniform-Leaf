#include "vec3.h"

// Constructors
Vec3::Vec3() : x(0), y(0), z(0) {}
Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

// Operator Overloads
Vec3 Vec3::operator+(const Vec3& other) const {
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const {
    return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(float scalar) const {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::operator/(float scalar) const {
    return Vec3(x / scalar, y / scalar, z / scalar);
}

bool Vec3::operator==(const Vec3& other) const {
    return (x == other.x && y == other.y && z == other.z);
}

// Dot Product
float Vec3::dot(const Vec3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

// Cross Product
Vec3 Vec3::cross(const Vec3& other) const {
    return Vec3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

// Magnitude
float Vec3::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

// Normalize
Vec3 Vec3::normalize() const {
    float mag = magnitude();
    return (mag > 0) ? (*this / mag) : Vec3(0, 0, 0);
}

// Static function: placeholder for QEF determinant
Vec3 Vec3::determinant(const std::vector<Vec3>& A) {
    Vec3 result(0, 0, 0);
    for (const auto& vec : A) {\n        // Placeholder: for each vector, multiply by its x component\n        result = result + (vec * vec.x);\n    }\n    return result;\n}

// Static function: placeholder for component-wise dot product across lists
Vec3 Vec3::dot(const std::vector<Vec3>& A, const std::vector<Vec3>& B) {\n    Vec3 result(0, 0, 0);\n    size_t n = A.size();\n    for (size_t i = 0; i < n; ++i) {\n        result = result + (A[i] * B[i].x); // Placeholder implementation\n    }\n    return result;\n}\n\n// Print function\nvoid Vec3::print() const {\n    std::cout << \"(\" << x << \", \" << y << \", \" << z << \")\" << std::endl;\n}\nEOF

###############################
# Create header: include/generation.h
###############################
cat << 'EOF' > "$PROJECT_ROOT/include/generation.h"
#ifndef GENERATION_H
#define GENERATION_H

#include "vec3.h"

namespace generation {
    float sphere(Vec3 p);
    Vec3 sphere_gradient(Vec3 p);
}

#endif // GENERATION_H
