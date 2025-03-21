/*
 * Copyright (C) Yakiv Matiash
 */

#pragma once

#include "pch.h"

namespace cgmath {

struct uint4 {
  uint32_t x, y, z, w;

  constexpr uint4() noexcept : x(0), y(0), z(0), w(0) {}
  constexpr uint4(uint32_t _x, uint32_t _y, uint32_t _z, uint32_t _w) noexcept : x(_x), y(_y), z(_z), w(_w) {}

  constexpr uint4 operator+(const uint4& v) const noexcept { return {x + v.x, y + v.y, z + v.z, w + v.w}; }
  constexpr uint4 operator-(const uint4& v) const noexcept { return {x - v.x, y - v.y, z - v.z, w - v.w}; }
  constexpr uint4 operator*(uint32_t scalar) const noexcept { return {x * scalar, y * scalar, z * scalar, w * scalar}; }
  constexpr uint4 operator%(uint32_t scalar) const noexcept { return {x % scalar, y % scalar, z % scalar, w % scalar}; }

  constexpr uint4& operator+=(const uint4& v) noexcept { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
  constexpr uint4& operator-=(const uint4& v) noexcept { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
  constexpr uint4& operator*=(uint32_t scalar) noexcept { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
  constexpr uint4& operator%=(uint32_t scalar) noexcept { x %= scalar; y %= scalar; z %= scalar; w %= scalar; return *this; }

  const char* to_string() const noexcept {
    static char buffer[64];
    std::snprintf(buffer, sizeof(buffer), "uint4(%u, %u, %u, %u)", x, y, z, w);
    return buffer;
  }
};

} // namespace cgmath

