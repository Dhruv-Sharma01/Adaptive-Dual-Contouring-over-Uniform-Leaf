#ifndef VEC3_H
#define VEC3_H

struct vec3 {
    float x, y, z;

    vec3();
    vec3(float x, float y, float z);

    vec3 operator+(const vec3 &other) const;
    vec3 operator-(const vec3 &other) const;
    vec3 operator*(float scalar) const;
    vec3 operator/(float scalar) const;
};

#endif // VEC3_H
