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
    struct { float x, y, z, w; } named;
  };

  constexpr vector4() noexcept : named{0.0f, 0.0f, 0.0f, 0.0f} {}
  constexpr vector4(float val) noexcept : named{val, val, val, val} {}
  constexpr vector4(float _x, float _y, float _z, float _w) noexcept : named{_x, _y, _z, _w} {}
  constexpr vector4(uint32_t _x, uint32_t _y, uint32_t _z, uint32_t _w) noexcept : vector4_u32{_x, _y, _z, _w} {}

#ifdef __SSE__
  vector4(__m128 v) noexcept { _mm_store_ps(vector4_f32, v); }
  __m128 to_m128() const noexcept { return _mm_load_ps(vector4_f32); }
#endif

  constexpr vector4 operator+(const vector4& v) const noexcept { return {named.x + v.named.x, named.y + v.named.y, named.z + v.named.z, named.w + v.named.w}; }
  constexpr vector4 operator-(const vector4& v) const noexcept { return {named.x - v.named.x, named.y - v.named.y, named.z - v.named.z, named.w - v.named.w}; }
  constexpr vector4 operator*(float scalar) const noexcept { return {named.x * scalar, named.y * scalar, named.z * scalar, named.w * scalar}; }
  constexpr vector4 operator/(float scalar) const noexcept { return {named.x / scalar, named.y / scalar, named.z / scalar, named.w / scalar}; }

  constexpr vector4& operator+=(const vector4& v) noexcept { named.x += v.named.x; named.y += v.named.y; named.z += v.named.z; named.w += v.named.w; return *this; }
  constexpr vector4& operator-=(const vector4& v) noexcept { named.x -= v.named.x; named.y -= v.named.y; named.z -= v.named.z; named.w -= v.named.w; return *this; }
  constexpr vector4& operator*=(float scalar) noexcept { named.x *= scalar; named.y *= scalar; named.z *= scalar; named.w *= scalar; return *this; }
  constexpr vector4& operator/=(float scalar) noexcept { named.x /= scalar; named.y /= scalar; named.z /= scalar; named.w /= scalar; return *this; }

  constexpr float dot(const vector4& v) const noexcept {
    return named.x * v.named.x + named.y * v.named.y + named.z * v.named.z + named.w * v.named.w;
  }

  constexpr float length() const noexcept {
    return std::sqrt(dot(*this));
  }

  constexpr vector4 normalized() const noexcept {
    float len = length();
    return len > 0 ? vector4{named.x / len, named.y / len, named.z / len, named.w / len} : vector4{0.0f, 0.0f, 0.0f, 0.0f};
  }

  constexpr vector4 clamp(const vector4& min, const vector4& max) const noexcept {
    return {
      std::fmax(min.named.x, std::fmin(named.x, max.named.x)),
      std::fmax(min.named.y, std::fmin(named.y, max.named.y)),
      std::fmax(min.named.z, std::fmin(named.z, max.named.z)),
      std::fmax(min.named.w, std::fmin(named.w, max.named.w))
    };
  }

  const char* to_string() const noexcept {
    static char buffer[64];
    std::snprintf(buffer, sizeof(buffer), "vector4(%.6f, %.6f, %.6f, %.6f)", named.x, named.y, named.z, named.w);
    return buffer;
  }
};

static_assert(sizeof(vector4) == 16, "vector4 must be 16 bytes");

} // namespace cg_math

