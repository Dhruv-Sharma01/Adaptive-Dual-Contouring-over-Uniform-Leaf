#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "vec3.h"

namespace functions {
    // Compute intersection along the edge p1-p2 given f(p1)=v1 and f(p2)=v2 (assumes v1 and v2 have opposite signs)
    Vec3 intersections(const Vec3& p1, const Vec3& p2, float v1, float v2);
}

#endif // FUNCTIONS_H
