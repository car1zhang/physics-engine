#pragma once

#include <glm/glm.hpp>


namespace Physics {

struct Vec2 {
    Vec2() : x(0.0f), y(0.0f) {}
    Vec2(float x, float y) : x(x), y(y) {}

    float x;
    float y;

    Vec2 operator+ (Vec2 other) {
        return Vec2(x + other.x, y + other.y);
    }
    Vec2 operator- (Vec2 other) {
        return Vec2(x - other.x, y - other.y);
    }
    Vec2 operator* (Vec2 other) {
        return Vec2(x * other.x, y * other.y);
    }
    Vec2 operator/ (Vec2 other) {
        return Vec2(x / other.x, y / other.y);
    }

    Vec2 operator* (float& s) {
        return Vec2(x * s, y * s);
    }
    Vec2 operator/ (float& s) {
        return Vec2(x / s, y / s);
    }

    float dot(Vec2 other) {
        return x * other.x + y * other.y;
    }

    float magnitude() {
        return sqrt(x * x + y * y);
    }
    Vec2 normalize() {
        return Vec2(x / magnitude(), y / magnitude());
    }

    glm::vec2 to_glm() {
        return glm::vec2(x, y);
    }
};

struct Vec3 {
    Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    float x;
    float y;
    float z;

    Vec3 operator+ (Vec3 other) {
        return Vec3(x + other.x, y + other.y, z + other.z);
    }
    Vec3 operator- (Vec3 other) {
        return Vec3(x - other.x, y - other.y, z - other.z);
    }
    Vec3 operator* (Vec3 other) {
        return Vec3(x * other.x, y * other.y, z * other.z);
    }
    Vec3 operator/ (Vec3 other) {
        return Vec3(x / other.x, y / other.y, z / other.z);
    }

    Vec3 operator* (float s) {
        return Vec3(x * s, y * s, z * s);
    }
    Vec3 operator/ (float s) {
        return Vec3(x / s, y / s, z / s);
    }

    float dot(Vec3 other) {
        return x * other.x + y * other.y + z * other.z;
    }
    Vec3 cross(Vec3 other) {
        return Vec3(y * other.z + z * other.y, x * other.z + z * other.x, y * other.x + x * other.y);
    }

    float magnitude() {
        return sqrt(x * x + y * y + z * z);
    }
    Vec3 normalize() {
        return *this / magnitude();
    }

    glm::vec3 to_glm() {
        return glm::vec3(x, y, z);
    }
};

// struct Vec4 {
//     Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
// 
//     float x;
//     float y;
//     float z;
//     float w;
// 
//     Vec4 operator+ (Vec4& other) {
//         return Vec4(x + other.x, y + other.y, z + other.z, w + other.w);
//     }
//     Vec4 operator- (Vec4& other) {
//         return Vec4(x - other.x, y - other.y, z - other.z, w + other.w);
//     }
// }
}
