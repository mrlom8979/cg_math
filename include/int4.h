/*
 * Copyright (C) Yakiv Matiash
 */

#pragma once

#include "pch.h"

namespace cgmath {

struct int4 {
  int32_t x, y, z, w;

  constexpr int4() noexcept : x(0), y(0), z(0), w(0) {}
  constexpr int4(int32_t _x, int32_t _y, int32_t _z, int32_t _w) noexcept : x(_x), y(_y), z(_z), w(_w) {}

  constexpr int4 operator+(const int4& v) const noexcept { return {x + v.x, y + v.y, z + v.z, w + v.w}; }
  constexpr int4 operator-(const int4& v) const noexcept { return {x - v.x, y - v.y, z - v.z, w - v.w}; }
  constexpr int4 operator*(int32_t scalar) const noexcept { return {x * scalar, y * scalar, z * scalar, w * scalar}; }
  constexpr int4 operator%(int32_t scalar) const noexcept { return {x % scalar, y % scalar, z % scalar, w % scalar}; }

  constexpr int4& operator+=(const int4& v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
  constexpr int4& operator-=(const int4& v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
  constexpr int4& operator*=(int32_t scalar) noexcept { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
  constexpr int4& operator%=(int32_t scalar) noexcept { x %= scalar; y %= scalar; z %= scalar; w %= scalar; return *this; }

  const char* to_string() const noexcept {
    static char buffer[64];
    std::snprintf(buffer, sizeof(buffer), "int4(%d, %d, %d, %d)", x, y, z, w);
    return buffer;
  }
};

} // namespace cgmath

