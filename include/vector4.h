/*
 * Copyright (C) Yakiv Matiash
 */

#pragma once

#include "pch.h"

namespace cg_math {

struct alignas(16) vector4
{
  union {
    float vector4_f32[4];
    uint32_t vector4_u32[4];
    struct { float x, y, z, w; } vec;
  };

  constexpr vector4() noexcept : vec{0.0f, 0.0f, 0.0f, 0.0f} {}
  constexpr vector4(float val) noexcept : vec{val, val, val, val} {}
  constexpr vector4(float _x, float _y, float _z, float _w) noexcept : vec{_x, _y, _z, _w} {}
  constexpr vector4(uint32_t _x, uint32_t _y, uint32_t _z, uint32_t _w) noexcept : vector4_u32{_x, _y, _z, _w} {}

#ifdef __SSE__
  vector4(__m128 v) noexcept { _mm_store_ps(vector4_f32, v); }
  __m128 to_m128() const noexcept { return _mm_load_ps(vector4_f32); }
#endif

  constexpr vector4 operator+(const vector4& v) const noexcept { return {vec.x + v.vec.x, vec.y + v.vec.y, vec.z + v.vec.z, vec.w + v.vec.w}; }
  constexpr vector4 operator-(const vector4& v) const noexcept { return {vec.x - v.vec.x, vec.y - v.vec.y, vec.z - v.vec.z, vec.w - v.vec.w}; }
  constexpr vector4 operator*(float scalar) const noexcept { return {vec.x * scalar, vec.y * scalar, vec.z * scalar, vec.w * scalar}; }
  constexpr vector4 operator/(float scalar) const noexcept { return {vec.x / scalar, vec.y / scalar, vec.z / scalar, vec.w / scalar}; }

  constexpr vector4& operator+=(const vector4& v) noexcept { vec.x += v.vec.x; vec.y += v.vec.y; vec.z += v.vec.z; vec.w += v.vec.w; return *this; }
  constexpr vector4& operator-=(const vector4& v) noexcept { vec.x -= v.vec.x; vec.y -= v.vec.y; vec.z -= v.vec.z; vec.w -= v.vec.w; return *this; }
  constexpr vector4& operator*=(float scalar) noexcept { vec.x *= scalar; vec.y *= scalar; vec.z *= scalar; vec.w *= scalar; return *this; }
  constexpr vector4& operator/=(float scalar) noexcept { vec.x /= scalar; vec.y /= scalar; vec.z /= scalar; vec.w /= scalar; return *this; }

  constexpr float dot(const vector4& v) const noexcept {
    return vec.x * v.vec.x + vec.y * v.vec.y + vec.z * v.vec.z + vec.w * v.vec.w;
  }

  constexpr float length() const noexcept {
    return std::sqrt(dot(*this));
  }

  constexpr vector4 normalized() const noexcept {
    float len = length();
    return len > 0 ? vector4{vec.x / len, vec.y / len, vec.z / len, vec.w / len} : vector4{0.0f, 0.0f, 0.0f, 0.0f};
  }

  constexpr vector4 clamp(const vector4& min, const vector4& max) const noexcept {
    return {
      std::fmax(min.vec.x, std::fmin(vec.x, max.vec.x)),
      std::fmax(min.vec.y, std::fmin(vec.y, max.vec.y)),
      std::fmax(min.vec.z, std::fmin(vec.z, max.vec.z)),
      std::fmax(min.vec.w, std::fmin(vec.w, max.vec.w))
    };
  }

  const char* to_string() const noexcept {
    static char buffer[64];
    std::snprintf(buffer, sizeof(buffer), "vector4(%.6f, %.6f, %.6f, %.6f)", vec.x, vec.y, vec.z, vec.w);
    return buffer;
  }
};

static_assert(sizeof(vector4) == 16, "vector4 must be 16 bytes");

} // namespace cg_math

