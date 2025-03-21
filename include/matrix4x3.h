/*
 * Copyright (C) Yakiv Matiash
 */

#pragma once

#include "pch.h"

namespace cgmath {

struct alignas(8) matrix4x3 {
  union {
    struct {
      float _11, _12, _13;
      float _21, _22, _23;
      float _31, _32, _33;
      float _41, _42, _43;
    } _m;
    float m[4][3];
  };

  matrix4x3() noexcept 
  : _m{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f} {}

  constexpr matrix4x3(float m00, float m01, float m02,
                      float m10, float m11, float m12,
                      float m20, float m21, float m22,
                      float m30, float m31, float m32) noexcept
  : _m{m00, m01, m02, m10, m11, m12, m20, m21, m22, m30, m31, m32} {}

  explicit matrix4x3(const float* arr) noexcept {
    _m._11 = arr[0]; _m._12 = arr[1]; _m._13 = arr[2];
    _m._21 = arr[3]; _m._22 = arr[4]; _m._23 = arr[5];
    _m._31 = arr[6]; _m._32 = arr[7]; _m._33 = arr[8];
    _m._41 = arr[9]; _m._42 = arr[10]; _m._43 = arr[11];
  }

  float operator()(size_t row, size_t col) const noexcept {
    return m[row][col];
  }

  float& operator()(size_t row, size_t col) noexcept {
    return m[row][col];
  }

  constexpr matrix4x3 operator+(const matrix4x3& other) const noexcept {
    return matrix4x3(
      _m._11 + other._m._11, _m._12 + other._m._12, _m._13 + other._m._13,
      _m._21 + other._m._21, _m._22 + other._m._22, _m._23 + other._m._23,
      _m._31 + other._m._31, _m._32 + other._m._32, _m._33 + other._m._33,
      _m._41 + other._m._41, _m._42 + other._m._42, _m._43 + other._m._43
    );
  }

  constexpr matrix4x3 operator-(const matrix4x3& other) const noexcept {
    return matrix4x3(
      _m._11 - other._m._11, _m._12 - other._m._12, _m._13 - other._m._13,
      _m._21 - other._m._21, _m._22 - other._m._22, _m._23 - other._m._23,
      _m._31 - other._m._31, _m._32 - other._m._32, _m._33 - other._m._33,
      _m._41 - other._m._41, _m._42 - other._m._42, _m._43 - other._m._43
    );
  }

  constexpr matrix4x3 operator*(float scalar) const noexcept {
    return matrix4x3(
      _m._11 * scalar, _m._12 * scalar, _m._13 * scalar,
      _m._21 * scalar, _m._22 * scalar, _m._23 * scalar,
      _m._31 * scalar, _m._32 * scalar, _m._33 * scalar,
      _m._41 * scalar, _m._42 * scalar, _m._43 * scalar
    );
  }

  constexpr matrix4x3 transpose() const noexcept {
    return matrix4x3(
      _m._11, _m._21, _m._31, _m._41,
      _m._12, _m._22, _m._32, _m._42,
      _m._13, _m._23, _m._33, _m._43
    );
  }

  void print() const noexcept {
    printf("| %.2f %.2f %.2f |\n", _m._11, _m._12, _m._13);
    printf("| %.2f %.2f %.2f |\n", _m._21, _m._22, _m._23);
    printf("| %.2f %.2f %.2f |\n", _m._31, _m._32, _m._33);
    printf("| %.2f %.2f %.2f |\n", _m._41, _m._42, _m._43);
  }

  const char* to_string() const noexcept {
    static char buffer[160];
    std::snprintf(buffer, sizeof(buffer),
                  "| %.2f %.2f %.2f |\n| %.2f %.2f %.2f |\n| %.2f %.2f %.2f |\n| %.2f %.2f %.2f |",
                  _m._11, _m._12, _m._13, _m._21, _m._22, _m._23, _m._31, _m._32, _m._33,
                  _m._41, _m._42, _m._43);
    return buffer;
  }

#if (__cplusplus >= 202002L)
  constexpr bool operator==(const matrix4x3& other) const noexcept = default;
  constexpr auto operator<=>(const matrix4x3& other) const noexcept = default;
#else
  constexpr bool operator==(const matrix4x3& other) const noexcept {
    return _m._11 == other._m._11 && _m._12 == other._m._12 && _m._13 == other._m._13 &&
    _m._21 == other._m._21 && _m._22 == other._m._22 && _m._23 == other._m._23 &&
    _m._31 == other._m._31 && _m._32 == other._m._32 && _m._33 == other._m._33 &&
    _m._41 == other._m._41 && _m._42 == other._m._42 && _m._43 == other._m._43;
  }
#endif
};

} // namespace cgmath

