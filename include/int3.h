/*
 * Copyright (C) Yakiv Matiash
 */

#pragma once

#include "pch.h"

namespace cgmath {

struct int3 {
  int32_t x, y, z;

  constexpr int3() noexcept : x(0), y(0), z(0) {}
  constexpr int3(int32_t _x, int32_t _y, int32_t _z) noexcept : x(_x), y(_y), z(_z) {}

  constexpr int3 operator+(const int3& v) const noexcept { return {x + v.x, y + v.y, z + v.z}; }
  constexpr int3 operator-(const int3& v) const noexcept { return {x - v.x, y - v.y, z - v.z}; }
  constexpr int3 operator*(int32_t scalar) const noexcept { return {x * scalar, y * scalar, z * scalar}; }
  constexpr int3 operator%(int32_t scalar) const noexcept { return {x % scalar, y % scalar, z % scalar}; }

  constexpr int3& operator+=(const int3& v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
  constexpr int3& operator-=(const int3& v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
  constexpr int3& operator*=(int32_t scalar) noexcept { x *= scalar; y *= scalar; z *= scalar; return *this; }
  constexpr int3& operator%=(int32_t scalar) noexcept { x %= scalar; y %= scalar; z %= scalar; return *this; }

  const char* to_string() const noexcept {
    static char buffer[48];
    std::snprintf(buffer, sizeof(buffer), "int3(%d, %d, %d)", x, y, z);
    return buffer;
  }
};

} // namespace cgmath

