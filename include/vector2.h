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
    struct { float x, y; } named;
  };

  constexpr vector2() noexcept : named{0.0f, 0.0f} {}
  constexpr vector2(float val) noexcept : named{val, val} {}
  constexpr vector2(float _x, float _y) noexcept : named{_x, _y} {}
  constexpr vector2(uint32_t _x, uint32_t _y) noexcept : vector2_u32{_x, _y} {}

#ifdef __SSE__
  vector2(__m128 v) noexcept { _mm_storel_pi((__m64*)vector2_f32, v); }
  __m128 to_m128() const noexcept { return _mm_loadl_pi(_mm_setzero_ps(), (__m64*)vector2_f32); }
#endif

  constexpr vector2 operator+(const vector2& v) const noexcept { return {named.x + v.named.x, named.y + v.named.y}; }
  constexpr vector2 operator-(const vector2& v) const noexcept { return {named.x - v.named.x, named.y - v.named.y}; }
  constexpr vector2 operator*(float scalar) const noexcept { return {named.x * scalar, named.y * scalar}; }
  constexpr vector2 operator/(float scalar) const noexcept { return {named.x / scalar, named.y / scalar}; }

  constexpr vector2& operator+=(const vector2& v) noexcept { named.x += v.named.x; named.y += v.named.y; return *this; }
  constexpr vector2& operator-=(const vector2& v) noexcept { named.x -= v.named.x; named.y -= v.named.y; return *this; }
  constexpr vector2& operator*=(float scalar) noexcept { named.x *= scalar; named.y *= scalar; return *this; }
  constexpr vector2& operator/=(float scalar) noexcept { named.x /= scalar; named.y /= scalar; return *this; }

  constexpr float length() const noexcept { return std::sqrt(named.x * named.x + named.y * named.y); }

  constexpr vector2 normalized() const noexcept {
    float len = length();
    return len > 0 ? vector2{named.x / len, named.y / len} : vector2{0.0f, 0.0f};
  }

  constexpr vector2 perpendicular() const noexcept {
    return {-named.y, named.x};
  }

  constexpr float dot(const vector2& v) const noexcept {
    return named.x * v.named.x + named.y * v.named.y;
  }

  constexpr float distance(const vector2& v) const noexcept {
    float dx = named.x - v.named.x;
    float dy = named.y - v.named.y;
    return std::sqrt(dx * dx + dy * dy);
  }

  constexpr vector2 clamp(const vector2& min, const vector2& max) const noexcept {
    return { 
      std::fmax(min.named.x, std::fmin(named.x, max.named.x)), 
      std::fmax(min.named.y, std::fmin(named.y, max.named.y)) 
    };
  }

  const char* to_string() const noexcept {
    static char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "vector2(%.6f, %.6f)", named.x, named.y);
    return buffer;
  }
};

static_assert(sizeof(vector2) == sizeof(float) * 2, "vector2 must be 8 bytes");

} // namespace cg_math

