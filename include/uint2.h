/*
 * Copyright (C) Yakiv Matiash
 */

#pragma once

#include "pch.h"

namespace cg_math {

struct uint2 {
  uint32_t x, y;

  constexpr uint2() noexcept : x(0), y(0) {}
  constexpr uint2(uint32_t _x, uint32_t _y) noexcept : x(_x), y(_y) {}

  constexpr uint2 operator+(const uint2& v) const noexcept { return {x + v.x, y + v.y}; }
  constexpr uint2 operator-(const uint2& v) const noexcept { return {x - v.x, y - v.y}; }
  constexpr uint2 operator*(uint32_t scalar) const noexcept { return {x * scalar, y * scalar}; }
  constexpr uint2 operator%(uint32_t scalar) const noexcept { return {x % scalar, y % scalar}; }

  constexpr uint2& operator+=(const uint2& v) noexcept { x += v.x; y += v.y; return *this; }
  constexpr uint2& operator-=(const uint2& v) noexcept { x -= v.x; y -= v.y; return *this; }
  constexpr uint2& operator*=(uint32_t scalar) noexcept { x *= scalar; y *= scalar; return *this; }
  constexpr uint2& operator%=(uint32_t scalar) noexcept { x %= scalar; y %= scalar; return *this; }

  const char* to_string() const noexcept {
    static char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "uint2(%u, %u)", x, y);
    return buffer;
  }
};

} // namespace cg_math

