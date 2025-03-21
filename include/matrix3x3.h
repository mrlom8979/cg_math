/*
 * Copyright (C) Yakiv Matiash
 */

#pragma once

#include "pch.h"

namespace cgmath {

struct alignas(8) matrix3x3 {
  union {
    struct {
      float _11, _12, _13;
      float _21, _22, _23;
      float _31, _32, _33;
    } _m;
    float m[3][3];
  };

  matrix3x3() noexcept 
  : _m{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f} {}

  constexpr matrix3x3(float m00, float m01, float m02,
                      float m10, float m11, float m12,
                      float m20, float m21, float m22) noexcept
  : _m{m00, m01, m02, m10, m11, m12, m20, m21, m22} {}

  explicit matrix3x3(const float* arr) noexcept {
    _m._11 = arr[0]; _m._12 = arr[1]; _m._13 = arr[2];
    _m._21 = arr[3]; _m._22 = arr[4]; _m._23 = arr[5];
    _m._31 = arr[6]; _m._32 = arr[7]; _m._33 = arr[8];
  }

  float operator()(size_t row, size_t col) const noexcept {
    return m[row][col];
  }

  float& operator()(size_t row, size_t col) noexcept {
    return m[row][col];
  }

  constexpr matrix3x3 operator+(const matrix3x3& other) const noexcept {
    return matrix3x3(
      _m._11 + other._m._11, _m._12 + other._m._12, _m._13 + other._m._13,
      _m._21 + other._m._21, _m._22 + other._m._22, _m._23 + other._m._23,
      _m._31 + other._m._31, _m._32 + other._m._32, _m._33 + other._m._33
    );
  }

  constexpr matrix3x3 operator-(const matrix3x3& other) const noexcept {
    return matrix3x3(
      _m._11 - other._m._11, _m._12 - other._m._12, _m._13 - other._m._13,
      _m._21 - other._m._21, _m._22 - other._m._22, _m._23 - other._m._23,
      _m._31 - other._m._31, _m._32 - other._m._32, _m._33 - other._m._33
    );
  }

  constexpr matrix3x3 operator*(float scalar) const noexcept {
    return matrix3x3(
      _m._11 * scalar, _m._12 * scalar, _m._13 * scalar,
      _m._21 * scalar, _m._22 * scalar, _m._23 * scalar,
      _m._31 * scalar, _m._32 * scalar, _m._33 * scalar
    );
  }

  constexpr matrix3x3 transpose() const noexcept {
    return matrix3x3(
      _m._11, _m._21, _m._31,
      _m._12, _m._22, _m._32,
      _m._13, _m._23, _m._33
    );
  }

  constexpr matrix3x3 operator*(const matrix3x3& other) const noexcept {
    return matrix3x3(
      _m._11 * other._m._11 + _m._12 * other._m._21 + _m._13 * other._m._31,
      _m._11 * other._m._12 + _m._12 * other._m._22 + _m._13 * other._m._32,
      _m._11 * other._m._13 + _m._12 * other._m._23 + _m._13 * other._m._33,
      _m._21 * other._m._11 + _m._22 * other._m._21 + _m._23 * other._m._31,
      _m._21 * other._m._12 + _m._22 * other._m._22 + _m._23 * other._m._32,
      _m._21 * other._m._13 + _m._22 * other._m._23 + _m._23 * other._m._33,
      _m._31 * other._m._11 + _m._32 * other._m._21 + _m._33 * other._m._31,
      _m._31 * other._m._12 + _m._32 * other._m._22 + _m._33 * other._m._32,
      _m._31 * other._m._13 + _m._32 * other._m._23 + _m._33 * other._m._33
    );
  }

  constexpr float determinant() const noexcept {
    return _m._11 * (_m._22 * _m._33 - _m._23 * _m._32) -
    _m._12 * (_m._21 * _m._33 - _m._23 * _m._31) +
    _m._13 * (_m._21 * _m._32 - _m._22 * _m._31);
  }

  constexpr bool is_invertible() const noexcept {
    return determinant() != 0.0f;
  }

  constexpr matrix3x3 inverse() const noexcept {
    float det = determinant();
    if (det == 0.0f) return matrix3x3{};

    float invDet = 1.0f / det;

    return matrix3x3(
      (_m._22 * _m._33 - _m._23 * _m._32) * invDet, (_m._13 * _m._32 - _m._12 * _m._33) * invDet, (_m._12 * _m._23 - _m._13 * _m._22) * invDet,
      (_m._23 * _m._31 - _m._21 * _m._33) * invDet, (_m._11 * _m._33 - _m._13 * _m._31) * invDet, (_m._13 * _m._21 - _m._11 * _m._23) * invDet,
      (_m._21 * _m._32 - _m._22 * _m._31) * invDet, (_m._12 * _m._31 - _m._11 * _m._32) * invDet, (_m._11 * _m._22 - _m._12 * _m._21) * invDet
    );
  }

  void print() const noexcept {
    printf("| %.2f %.2f %.2f |\n", _m._11, _m._12, _m._13);
    printf("| %.2f %.2f %.2f |\n", _m._21, _m._22, _m._23);
    printf("| %.2f %.2f %.2f |\n", _m._31, _m._32, _m._33);
  }

  const char* to_string() const noexcept {
    static char buffer[128];
    std::snprintf(buffer, sizeof(buffer),
                  "| %.2f %.2f %.2f |\n| %.2f %.2f %.2f |\n| %.2f %.2f %.2f |",
                  _m._11, _m._12, _m._13, _m._21, _m._22, _m._23, _m._31, _m._32, _m._33);
    return buffer;
  }

#if (__cplusplus >= 202002L)
  constexpr bool operator==(const matrix3x3& other) const noexcept = default;
  constexpr auto operator<=>(const matrix3x3& other) const noexcept = default;
#else
  constexpr bool operator==(const matrix3x3& other) const noexcept {
    return _m._11 == other._m._11 && _m._12 == other._m._12 && _m._13 == other._m._13 &&
    _m._21 == other._m._21 && _m._22 == other._m._22 && _m._23 == other._m._23 &&
    _m._31 == other._m._31 && _m._32 == other._m._32 && _m._33 == other._m._33;
  }
#endif
};

} // namespace cgmath

