#include "functions.h"
#include <cmath>

namespace functions {
    Vec3 intersections(const Vec3& p1, const Vec3& p2, float v1, float v2) {
        float t = (0 - v1) / (v2 - v1);
        return Vec3(p1.x + t * (p2.x - p1.x),
                    p1.y + t * (p2.y - p1.y),
                    p1.z + t * (p2.z - p1.z));
    }
}
