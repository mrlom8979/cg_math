/*
 * Copyright (C) Yakiv Matiash
 */

#pragma once

#include "float2.h"
#include "float3.h"
#include "float4.h"

#include "int2.h"
#include "int3.h"
#include "int4.h"

#include "uint2.h"
#include "uint3.h"
#include "uint4.h"

#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

#include "matrix3x3.h"
#include "matrix3x4.h"
#include "matrix4x3.h"
#include "matrix4x4.h"

namespace cgmath {

constexpr float PI        = 3.14159265358979323846f;
constexpr float TWO_PI    = 6.28318530717958647692f;
constexpr float HALF_PI   = 1.57079632679489661923f;
constexpr float INV_PI    = 0.31830988618379067153f; // 1 / PI
constexpr float DEG2RAD   = PI / 180.0f;
constexpr float RAD2DEG   = 180.0f / PI;
constexpr float EPSILON   = 1e-6f;
constexpr float INF       = std::numeric_limits<float>::infinity();

// Conversion functions between degrees and radians
constexpr float to_radians(float deg) noexcept { return deg * DEG2RAD; }
constexpr float to_degrees(float rad) noexcept { return rad * RAD2DEG; }

// Arithmetic functions
constexpr float abs(float x) noexcept { return x < 0 ? -x : x; }
constexpr float min(float a, float b) noexcept { return (a < b) ? a : b; }
constexpr float max(float a, float b) noexcept { return (a > b) ? a : b; }
constexpr float clamp(float x, float minVal, float maxVal) noexcept { return max(min(x, maxVal), minVal); }

// Interpolation
constexpr float lerp(float a, float b, float t) noexcept { return a + t * (b - a); }
constexpr float smoothstep(float edge0, float edge1, float x) noexcept {
    float t = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return t * t * (3.0f - 2.0f * t);
}
constexpr float step(float edge, float x) noexcept { return x < edge ? 0.0f : 1.0f; }

// Trigonometry
inline float sin(float x) noexcept { return std::sin(x); }
inline float cos(float x) noexcept { return std::cos(x); }
inline float tan(float x) noexcept { return std::tan(x); }
inline float asin(float x) noexcept { return std::asin(x); }
inline float acos(float x) noexcept { return std::acos(x); }
inline float atan(float x) noexcept { return std::atan(x); }
inline float atan2(float y, float x) noexcept { return std::atan2(y, x); }

// Power and logarithms
inline float pow(float x, float y) noexcept { return std::pow(x, y); }
inline float sqrt(float x) noexcept { return std::sqrt(x); }
inline float rsqrt(float x) noexcept { return 1.0f / sqrt(x); }
inline float log(float x) noexcept { return std::log(x); }
inline float log2(float x) noexcept { return std::log2(x); }
inline float log10(float x) noexcept { return std::log10(x); }

// Rounding functions
inline float floor(float x) noexcept { return std::floor(x); }
inline float ceil(float x) noexcept { return std::ceil(x); }
inline float round(float x) noexcept { return std::round(x); }
inline float fract(float x) noexcept { return x - floor(x); }
inline float trunc(float x) noexcept { return std::trunc(x); }

// Constants of the Golden Ratio
constexpr float PHI       = 1.618033988749895f;  // Golden ratio (φ)
constexpr float INV_PHI   = 0.618033988749895f;  // 1 / φ
constexpr float FIB_RATIO = 1.618f;             // Fibonacci Approximate Ratio

// Physical constants
constexpr float SPEED_OF_LIGHT = 299792458.0f; // m/s
constexpr float GRAVITY        = 9.80665f;     // m/s²
constexpr float PLANCK         = 6.62607015e-34f; // Planck's constant
constexpr float BOLTZMANN      = 1.380649e-23f;  // Boltzmann constant

// Vectors of zeros and ones for convenience
constexpr float2 ZERO_FLOAT2  = {0.0f, 0.0f};
constexpr float3 ZERO_FLOAT3  = {0.0f, 0.0f, 0.0f};
constexpr float4 ZERO_FLOAT4  = {0.0f, 0.0f, 0.0f, 0.0f};

constexpr int2 ZERO_INT2      = {0, 0};
constexpr int3 ZERO_INT3      = {0, 0, 0};
constexpr int4 ZERO_INT4      = {0, 0, 0, 0};

constexpr uint2 ZERO_UINT2    = {0, 0};
constexpr uint3 ZERO_UINT3    = {0, 0, 0};
constexpr uint4 ZERO_UINT4    = {0, 0, 0, 0};

constexpr float2 ONE_FLOAT2   = {1.0f, 1.0f};
constexpr float3 ONE_FLOAT3   = {1.0f, 1.0f, 1.0f};
constexpr float4 ONE_FLOAT4   = {1.0f, 1.0f, 1.0f, 1.0f};

constexpr int2 ONE_INT2       = {1, 1};
constexpr int3 ONE_INT3       = {1, 1, 1};
constexpr int4 ONE_INT4       = {1, 1, 1, 1};

constexpr uint2 ONE_UINT2     = {1, 1};
constexpr uint3 ONE_UINT3     = {1, 1, 1};
constexpr uint4 ONE_UINT4     = {1, 1, 1, 1};

} // namespace cgmath
