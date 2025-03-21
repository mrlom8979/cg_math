/*
 * Copyright (C) Yakiv Matiash
 */

#pragma once

#include "pch.h"

namespace cg_math {

struct alignas(8) vector2
{
  union {
    float vector2_f32[2];
    uint32_t vector2_u32[2];
    struct { float x, y; } vec;
  };

  constexpr vector2() noexcept : vec{0.0f, 0.0f} {}
  constexpr vector2(float val) noexcept : vec{val, val} {}
  constexpr vector2(float _x, float _y) noexcept : vec{_x, _y} {}
  constexpr vector2(uint32_t _x, uint32_t _y) noexcept : vector2_u32{_x, _y} {}

#ifdef __SSE__
  vector2(__m128 v) noexcept { _mm_storel_pi((__m64*)vector2_f32, v); }
  __m128 to_m128() const noexcept { return _mm_loadl_pi(_mm_setzero_ps(), (__m64*)vector2_f32); }
#endif

  constexpr vector2 operator+(const vector2& v) const noexcept { return {vec.x + v.vec.x, vec.y + v.vec.y}; }
  constexpr vector2 operator-(const vector2& v) const noexcept { return {vec.x - v.vec.x, vec.y - v.vec.y}; }
  constexpr vector2 operator*(float scalar) const noexcept { return {vec.x * scalar, vec.y * scalar}; }
  constexpr vector2 operator/(float scalar) const noexcept { return {vec.x / scalar, vec.y / scalar}; }

  constexpr vector2& operator+=(const vector2& v) noexcept { vec.x += v.vec.x; vec.y += v.vec.y; return *this; }
  constexpr vector2& operator-=(const vector2& v) noexcept { vec.x -= v.vec.x; vec.y -= v.vec.y; return *this; }
  constexpr vector2& operator*=(float scalar) noexcept { vec.x *= scalar; vec.y *= scalar; return *this; }
  constexpr vector2& operator/=(float scalar) noexcept { vec.x /= scalar; vec.y /= scalar; return *this; }

  constexpr float length() const noexcept { return std::sqrt(vec.x * vec.x + vec.y * vec.y); }

  constexpr vector2 normalized() const noexcept {
    float len = length();
    return len > 0 ? vector2{vec.x / len, vec.y / len} : vector2{0.0f, 0.0f};
  }

  constexpr vector2 perpendicular() const noexcept {
    return {-vec.y, vec.x};
  }

  constexpr float dot(const vector2& v) const noexcept {
    return vec.x * v.vec.x + vec.y * v.vec.y;
  }

  constexpr float distance(const vector2& v) const noexcept {
    float dx = vec.x - v.vec.x;
    float dy = vec.y - v.vec.y;
    return std::sqrt(dx * dx + dy * dy);
  }

  constexpr vector2 clamp(const vector2& min, const vector2& max) const noexcept {
    return { 
      std::fmax(min.vec.x, std::fmin(vec.x, max.vec.x)), 
      std::fmax(min.vec.y, std::fmin(vec.y, max.vec.y)) 
    };
  }

  const char* to_string() const noexcept {
    static char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "vector2(%.6f, %.6f)", vec.x, vec.y);
    return buffer;
  }
};

static_assert(sizeof(vector2) == sizeof(float) * 2, "vector2 must be 8 bytes");

} // namespace cg_math

