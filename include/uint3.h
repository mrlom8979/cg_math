/*
 * Copyright (C) Yakiv Matiash
 */

#pragma once

#include "pch.h"

namespace cg_math {

struct uint3 {
  uint32_t x, y, z;

  constexpr uint3() noexcept : x(0), y(0), z(0) {}
  constexpr uint3(uint32_t _x, uint32_t _y, uint32_t _z) noexcept : x(_x), y(_y), z(_z) {}

  constexpr uint3 operator+(const uint3& v) const noexcept { return {x + v.x, y + v.y, z + v.z}; }
  constexpr uint3 operator-(const uint3& v) const noexcept { return {x - v.x, y - v.y, z - v.z}; }
  constexpr uint3 operator*(uint32_t scalar) const noexcept { return {x * scalar, y * scalar, z * scalar}; }
  constexpr uint3 operator%(uint32_t scalar) const noexcept { return {x % scalar, y % scalar, z % scalar}; }

  constexpr uint3& operator+=(const uint3& v) noexcept { x += v.x; y += v.y; z += v.z; return *this; }
  constexpr uint3& operator-=(const uint3& v) noexcept { x -= v.x; y -= v.y; z -= v.z; return *this; }
  constexpr uint3& operator*=(uint32_t scalar) noexcept { x *= scalar; y *= scalar; z *= scalar; return *this; }
  constexpr uint3& operator%=(uint32_t scalar) noexcept { x %= scalar; y %= scalar; z %= scalar; return *this; }

  const char* to_string() const noexcept {
    static char buffer[48];
    std::snprintf(buffer, sizeof(buffer), "uint3(%u, %u, %u)", x, y, z);
    return buffer;
  }
};

} // namespace cg_math

