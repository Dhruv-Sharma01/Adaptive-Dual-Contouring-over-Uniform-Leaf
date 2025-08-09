#ifndef GENERATION_H
#define GENERATION_H

#include "vec3.h"

namespace generation {
    float sphere(Vec3 p);
    Vec3 sphere_gradient(Vec3 p);

    float torus(Vec3 p);
    Vec3 torus_gradient(Vec3 p);

    float cube(Vec3 p);
    Vec3 cube_gradient(Vec3 p);

    float gyroid(Vec3 p);
    Vec3 gyroid_gradient(Vec3 p);
}

#endif // GENERATION_H
