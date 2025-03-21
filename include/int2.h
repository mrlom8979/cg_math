/*
 * Copyright (C) Yakiv Matiash
 */

#pragma once

#include "pch.h"

namespace cgmath {

struct int2 {
  int32_t x, y;

  constexpr int2() noexcept : x(0), y(0) {}
  constexpr int2(int32_t _x, int32_t _y) noexcept : x(_x), y(_y) {}

  constexpr int2 operator+(const int2& v) const noexcept { return {x + v.x, y + v.y}; }
  constexpr int2 operator-(const int2& v) const noexcept { return {x - v.x, y - v.y}; }
  constexpr int2 operator*(int32_t scalar) const noexcept { return {x * scalar, y * scalar}; }
  constexpr int2 operator%(int32_t scalar) const noexcept { return {x % scalar, y % scalar}; }

  constexpr int2& operator+=(const int2& v) noexcept { x += v.x; y += v.y; return *this; }
  constexpr int2& operator-=(const int2& v) noexcept { x -= v.x; y -= v.y; return *this; }
  constexpr int2& operator*=(int32_t scalar) noexcept { x *= scalar; y *= scalar; return *this; }
  constexpr int2& operator%=(int32_t scalar) noexcept { x %= scalar; y %= scalar; return *this; }

  const char* to_string() const noexcept {
    static char buffer[32];
    std::snprintf(buffer, sizeof(buffer), "int2(%d, %d)", x, y);
    return buffer;
  }
};

} // namespace cgmath

