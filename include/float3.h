/*
 * Copyright (C) Yakiv Matiash
 */

#pragma once
#include <cmath>
#include <type_traits>

namespace cg_math {

struct float3
{
    float x, y, z;

    constexpr float3() noexcept : x(0.0f), y(0.0f), z(0.0f) {}
    constexpr float3(float _x, float _y, float _z) noexcept : x(_x), y(_y), z(_z) {}

    constexpr float3(const float3&) noexcept = default;
    constexpr float3(float3&&) noexcept = default;
    constexpr float3& operator=(const float3&) noexcept = default;
    constexpr float3& operator=(float3&&) noexcept = default;

#if (__cplusplus >= 202002L)
    constexpr bool operator==(const float3&) const noexcept = default;
    constexpr auto operator<=>(const float3&) const noexcept = default;
#else
    constexpr bool operator==(const float3& other) const noexcept {
        return x == other.x && y == other.y && z == other.z;
    }
#endif

    constexpr float3 operator+(const float3& v) const noexcept { return {x + v.x, y + v.y, z + v.z}; }
    constexpr float3 operator-(const float3& v) const noexcept { return {x - v.x, y - v.y, z - v.z}; }
    constexpr float3 operator*(float scalar) const noexcept { return {x * scalar, y * scalar, z * scalar}; }
    constexpr float3 operator/(float scalar) const noexcept { return {x / scalar, y / scalar, z / scalar}; }

    constexpr float3& operator+=(const float3& v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
    constexpr float3& operator-=(const float3& v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
    constexpr float3& operator*=(float scalar) noexcept { x *= scalar; y *= scalar; z *= scalar; return *this; }
    constexpr float3& operator/=(float scalar) noexcept { x /= scalar; y /= scalar; z /= scalar; return *this; }

    constexpr float length() const noexcept { return std::sqrt(x * x + y * y + z * z); }

    constexpr float3 normalized() const noexcept {
        float len = length();
        return len > 0 ? float3{x / len, y / len, z / len} : float3{0.0f, 0.0f, 0.0f};
    }

    constexpr float dot(const float3& v) const noexcept {
        return x * v.x + y * v.y + z * v.z;
    }

    constexpr float3 cross(const float3& v) const noexcept {
        return {
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        };
    }
};

static_assert(sizeof(float3) == sizeof(float) * 3, "float3 must be 12 bytes");

} // namespace cg_math

