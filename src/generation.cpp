#include "generation.h"

namespace generation {
    float sphere(Vec3 p) {
        return p.x * p.x + p.y * p.y + p.z * p.z - 1.0f;
    }
    Vec3 sphere_gradient(Vec3 p) {
        return Vec3(2 * p.x, 2 * p.y, 2 * p.z);
    }
}
