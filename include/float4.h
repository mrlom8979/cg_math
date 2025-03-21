/*
 * Copyright (C) Yakiv Matiash
 */

#pragma once
#include <cmath>
#include <type_traits>

namespace cg_math {

struct float4
{
    float x, y, z, w;

    constexpr float4() noexcept : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    constexpr float4(float _x, float _y, float _z, float _w) noexcept : x(_x), y(_y), z(_z), w(_w) {}

    constexpr float4(const float4&) noexcept = default;
    constexpr float4(float4&&) noexcept = default;
    constexpr float4& operator=(const float4&) noexcept = default;
    constexpr float4& operator=(float4&&) noexcept = default;

#if (__cplusplus >= 202002L)
    constexpr bool operator==(const float4&) const noexcept = default;
    constexpr auto operator<=>(const float4&) const noexcept = default;
#else
    constexpr bool operator==(const float4& other) const noexcept {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }
#endif

    constexpr float4 operator+(const float4& v) const noexcept { return {x + v.x, y + v.y, z + v.z, w + v.w}; }
    constexpr float4 operator-(const float4& v) const noexcept { return {x - v.x, y - v.y, z - v.z, w - v.w}; }
    constexpr float4 operator*(float scalar) const noexcept { return {x * scalar, y * scalar, z * scalar, w * scalar}; }
    constexpr float4 operator/(float scalar) const noexcept { return {x / scalar, y / scalar, z / scalar, w / scalar}; }

    constexpr float4& operator+=(const float4& v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
    constexpr float4& operator-=(const float4& v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
    constexpr float4& operator*=(float scalar) noexcept { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
    constexpr float4& operator/=(float scalar) noexcept { x /= scalar; y /= scalar; z /= scalar; w /= scalar; return *this; }

    constexpr float length() const noexcept { return std::sqrt(x * x + y * y + z * z + w * w); }

    constexpr float4 normalized() const noexcept {
        float len = length();
        return len > 0 ? float4{x / len, y / len, z / len, w / len} : float4{0.0f, 0.0f, 0.0f, 0.0f};
    }

    constexpr float dot(const float4& v) const noexcept {
        return x * v.x + y * v.y + z * v.z + w * v.w;
    }
};

static_assert(sizeof(float4) == sizeof(float) * 4, "float4 must be 16 bytes");

} // namespace cg_math

