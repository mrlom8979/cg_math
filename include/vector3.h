/*
 * Copyright (C) Yakiv Matiash
 */

#pragma once

#include "pch.h"

namespace cg_math {

struct alignas(16) vector3
{
  union {
    float vector3_f32[3];
    uint32_t vector3_u32[3];
    struct { float x, y, z; } vec;
  };

  constexpr vector3() noexcept : vec{0.0f, 0.0f, 0.0f} {}
  constexpr vector3(float val) noexcept : vec{val, val, val} {}
  constexpr vector3(float _x, float _y, float _z) noexcept : vec{_x, _y, _z} {}
  constexpr vector3(uint32_t _x, uint32_t _y, uint32_t _z) noexcept : vector3_u32{_x, _y, _z} {}

#ifdef __SSE__
  vector3(__m128 v) noexcept { _mm_store_ps(vector3_f32, v); }
  __m128 to_m128() const noexcept { return _mm_load_ps(vector3_f32); }
#endif

  constexpr vector3 operator+(const vector3& v) const noexcept { return {vec.x + v.vec.x, vec.y + v.vec.y, vec.z + v.vec.z}; }
  constexpr vector3 operator-(const vector3& v) const noexcept { return {vec.x - v.vec.x, vec.y - v.vec.y, vec.z - v.vec.z}; }
  constexpr vector3 operator*(float scalar) const noexcept { return {vec.x * scalar, vec.y * scalar, vec.z * scalar}; }
  constexpr vector3 operator/(float scalar) const noexcept { return {vec.x / scalar, vec.y / scalar, vec.z / scalar}; }

  constexpr vector3& operator+=(const vector3& v) noexcept { vec.x += v.vec.x; vec.y += v.vec.y; vec.z += v.vec.z; return *this; }
  constexpr vector3& operator-=(const vector3& v) noexcept { vec.x -= v.vec.x; vec.y -= v.vec.y; vec.z -= v.vec.z; return *this; }
  constexpr vector3& operator*=(float scalar) noexcept { vec.x *= scalar; vec.y *= scalar; vec.z *= scalar; return *this; }
  constexpr vector3& operator/=(float scalar) noexcept { vec.x /= scalar; vec.y /= scalar; vec.z /= scalar; return *this; }

  constexpr float length() const noexcept { return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z); }

  constexpr vector3 normalized() const noexcept {
    float len = length();
    return len > 0 ? vector3{vec.x / len, vec.y / len, vec.z / len} : vector3{0.0f, 0.0f, 0.0f};
  }

  constexpr float dot(const vector3& v) const noexcept {
    return vec.x * v.vec.x + vec.y * v.vec.y + vec.z * v.vec.z;
  }

  constexpr vector3 cross(const vector3& v) const noexcept {
    return {
      vec.y * v.vec.z - vec.z * v.vec.y,
      vec.z * v.vec.x - vec.x * v.vec.z,
      vec.x * v.vec.y - vec.y * v.vec.x
    };
  }

  constexpr float distance(const vector3& v) const noexcept {
    float dx = vec.x - v.vec.x;
    float dy = vec.y - v.vec.y;
    float dz = vec.z - v.vec.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
  }

  constexpr vector3 clamp(const vector3& min, const vector3& max) const noexcept {
    return {
      std::fmax(min.vec.x, std::fmin(vec.x, max.vec.x)), 
      std::fmax(min.vec.y, std::fmin(vec.y, max.vec.y)), 
      std::fmax(min.vec.z, std::fmin(vec.z, max.vec.z))
    };
  }

  const char* to_string() const noexcept {
    static char buffer[48];
    std::snprintf(buffer, sizeof(buffer), "vector3(%.6f, %.6f, %.6f)", vec.x, vec.y, vec.z);
    return buffer;
  }
};

static_assert(sizeof(vector3) == 16, "vector3 must be 16 bytes");

} // namespace cg_math

