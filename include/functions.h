#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "vec3.h"
#include <vector>

// Forward declaration to avoid circular dependency
namespace octree {
    class Cell;
}

namespace functions {
    Vec3 intersections(const Vec3& p1, const Vec3& p2, float v1, float v2);
    std::vector<std::vector<Vec3>> triangulate();
}

#endif // FUNCTIONS_H
