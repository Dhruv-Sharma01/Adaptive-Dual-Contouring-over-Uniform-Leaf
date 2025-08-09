#include "generation.h"
#include <cmath>
#include <algorithm>

namespace generation {
    float sphere(Vec3 p) {
        return p.x * p.x + p.y * p.y + p.z * p.z - 1.0f;
    }

    Vec3 sphere_gradient(Vec3 p) {
        return Vec3(2 * p.x, 2 * p.y, 2 * p.z);
    }

    float torus(Vec3 p) {
        float R = 1.0f; // Major radius
        float r = 0.3f; // Minor radius
        float q = sqrt(p.x * p.x + p.z * p.z) - R;
        return q * q + p.y * p.y - r * r;
    }

    Vec3 torus_gradient(Vec3 p) {
        float R = 1.0f;
        float r = 0.3f;
        float q = sqrt(p.x * p.x + p.z * p.z) - R;
        float len_xz = sqrt(p.x * p.x + p.z * p.z);

        if (len_xz == 0) return Vec3(1, 0, 0);

        float dx = 2 * q * (p.x / len_xz);
        float dy = 2 * p.y;
        float dz = 2 * q * (p.z / len_xz);

        return Vec3(dx, dy, dz);
    }

    float cube(Vec3 p) {
        float size = 0.8f;
        float dx = std::max(std::abs(p.x) - size, 0.0f);
        float dy = std::max(std::abs(p.y) - size, 0.0f);
        float dz = std::max(std::abs(p.z) - size, 0.0f);
        return dx * dx + dy * dy + dz * dz +
               std::min(std::max({std::abs(p.x) - size, std::abs(p.y) - size, std::abs(p.z) - size}), 0.0f);
    }

    Vec3 cube_gradient(Vec3 p) {
        float eps = 0.001f;
        float dx = (cube(Vec3(p.x + eps, p.y, p.z)) - cube(Vec3(p.x - eps, p.y, p.z))) / (2.0f * eps);
        float dy = (cube(Vec3(p.x, p.y + eps, p.z)) - cube(Vec3(p.x, p.y - eps, p.z))) / (2.0f * eps);
        float dz = (cube(Vec3(p.x, p.y, p.z + eps)) - cube(Vec3(p.x, p.y, p.z - eps))) / (2.0f * eps);
        return Vec3(dx, dy, dz);
    }

    float gyroid(Vec3 p) {
        float scale = 2.0f;
        return sin(scale * p.x) * cos(scale * p.y) +
               sin(scale * p.y) * cos(scale * p.z) +
               sin(scale * p.z) * cos(scale * p.x);
    }

    Vec3 gyroid_gradient(Vec3 p) {
        float scale = 2.0f;
        float dx = scale * cos(scale * p.x) * cos(scale * p.y) - scale * sin(scale * p.z) * sin(scale * p.x);
        float dy = -scale * sin(scale * p.x) * sin(scale * p.y) + scale * cos(scale * p.y) * cos(scale * p.z);
        float dz = -scale * sin(scale * p.y) * sin(scale * p.z) + scale * cos(scale * p.z) * cos(scale * p.x);
        return Vec3(dx, dy, dz);
    }
}
