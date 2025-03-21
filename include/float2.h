/*
 * Copyright (C) Yakiv Matiash
 */

#pragma once

#include "pch.h"

namespace cgmath {

struct float2
{
  float x, y;

  constexpr float2() noexcept : x(0.0f), y(0.0f) {}
  constexpr float2(float _x, float _y) noexcept : x(_x), y(_y) {}

  constexpr float2(const float2&) noexcept = default;
  constexpr float2(float2&&) noexcept = default;
  constexpr float2& operator=(const float2&) noexcept = default;
  constexpr float2& operator=(float2&&) noexcept = default;

#if (__cplusplus >= 202002L)
  constexpr bool operator==(const float2&) const noexcept = default;
  constexpr auto operator<=>(const float2&) const noexcept = default;
#else
  constexpr bool operator==(const float2& other) const noexcept {
    return x == other.x && y == other.y;
  }
#endif

  constexpr float2 operator+(const float2& v) const noexcept { return {x + v.x, y + v.y}; }
  constexpr float2 operator-(const float2& v) const noexcept { return {x - v.x, y - v.y}; }
  constexpr float2 operator*(float scalar) const noexcept { return {x * scalar, y * scalar}; }
  constexpr float2 operator/(float scalar) const noexcept { return {x / scalar, y / scalar}; }

  constexpr float2& operator+=(const float2& v) noexcept { x += v.x; y += v.y; return *this; }
  constexpr float2& operator-=(const float2& v) noexcept { x -= v.x; y -= v.y; return *this; }
  constexpr float2& operator*=(float scalar) noexcept { x *= scalar; y *= scalar; return *this; }
  constexpr float2& operator/=(float scalar) noexcept { x /= scalar; y /= scalar; return *this; }

  constexpr float length() const noexcept { return std::sqrt(x * x + y * y); }

  constexpr float2 normalized() const noexcept {
    float len = length();
    return len > 0 ? float2{x / len, y / len} : float2{0.0f, 0.0f};
  }

  const char* to_string() const noexcept {
    static char buffer[32]; // Буфер на 32 символа (должно хватить для float)
    std::snprintf(buffer, sizeof(buffer), "float2(%.6f, %.6f)", x, y);
    return buffer;
  }
};

static_assert(sizeof(float2) == sizeof(float) * 2, "float2 must be 8 bytes");

} // namespace cgmath

