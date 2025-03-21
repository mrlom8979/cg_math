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
    struct { float x, y, z; } named;
  };

  constexpr vector3() noexcept : named{0.0f, 0.0f, 0.0f} {}
  constexpr vector3(float val) noexcept : named{val, val, val} {}
  constexpr vector3(float _x, float _y, float _z) noexcept : named{_x, _y, _z} {}
  constexpr vector3(uint32_t _x, uint32_t _y, uint32_t _z) noexcept : vector3_u32{_x, _y, _z} {}

#ifdef __SSE__
  vector3(__m128 v) noexcept { _mm_store_ps(vector3_f32, v); }
  __m128 to_m128() const noexcept { return _mm_load_ps(vector3_f32); }
#endif

  constexpr vector3 operator+(const vector3& v) const noexcept { return {named.x + v.named.x, named.y + v.named.y, named.z + v.named.z}; }
  constexpr vector3 operator-(const vector3& v) const noexcept { return {named.x - v.named.x, named.y - v.named.y, named.z - v.named.z}; }
  constexpr vector3 operator*(float scalar) const noexcept { return {named.x * scalar, named.y * scalar, named.z * scalar}; }
  constexpr vector3 operator/(float scalar) const noexcept { return {named.x / scalar, named.y / scalar, named.z / scalar}; }

  constexpr vector3& operator+=(const vector3& v) noexcept { named.x += v.named.x; named.y += v.named.y; named.z += v.named.z; return *this; }
  constexpr vector3& operator-=(const vector3& v) noexcept { named.x -= v.named.x; named.y -= v.named.y; named.z -= v.named.z; return *this; }
  constexpr vector3& operator*=(float scalar) noexcept { named.x *= scalar; named.y *= scalar; named.z *= scalar; return *this; }
  constexpr vector3& operator/=(float scalar) noexcept { named.x /= scalar; named.y /= scalar; named.z /= scalar; return *this; }

  constexpr float length() const noexcept { return std::sqrt(named.x * named.x + named.y * named.y + named.z * named.z); }

  constexpr vector3 normalized() const noexcept {
    float len = length();
    return len > 0 ? vector3{named.x / len, named.y / len, named.z / len} : vector3{0.0f, 0.0f, 0.0f};
  }

  constexpr float dot(const vector3& v) const noexcept {
    return named.x * v.named.x + named.y * v.named.y + named.z * v.named.z;
  }

  constexpr vector3 cross(const vector3& v) const noexcept {
    return {
      named.y * v.named.z - named.z * v.named.y,
      named.z * v.named.x - named.x * v.named.z,
      named.x * v.named.y - named.y * v.named.x
    };
  }

  constexpr float distance(const vector3& v) const noexcept {
    float dx = named.x - v.named.x;
    float dy = named.y - v.named.y;
    float dz = named.z - v.named.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
  }

  constexpr vector3 clamp(const vector3& min, const vector3& max) const noexcept {
    return {
      std::fmax(min.named.x, std::fmin(named.x, max.named.x)), 
      std::fmax(min.named.y, std::fmin(named.y, max.named.y)), 
      std::fmax(min.named.z, std::fmin(named.z, max.named.z))
    };
  }

  const char* to_string() const noexcept {
    static char buffer[48];
    std::snprintf(buffer, sizeof(buffer), "vector3(%.6f, %.6f, %.6f)", named.x, named.y, named.z);
    return buffer;
  }
};

static_assert(sizeof(vector3) == 16, "vector3 must be 16 bytes");

} // namespace cg_math

