#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "octree.h"
#include "vec3.h"

namespace functions {
    Vec3 intersections(const Vec3& p1, const Vec3& p2, float v1, float v2);
    vector<vector<vec3>> triangulate();
}

#endif // FUNCTIONS_H
