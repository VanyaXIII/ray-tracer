#pragma once
#include <array>
#include <emmintrin.h>
#include <nlohmann/json.hpp>

#include "vector3.h"

using namespace nlohmann;

inline double sqrt_simd(double f) {
  __m128d temp = _mm_set_sd(f);
  temp = _mm_sqrt_sd(temp, temp);
  return _mm_cvtsd_f64(temp);
}

inline double mul_simd(double a, double b) {
  return _mm_cvtsd_f64(_mm_mul_sd(_mm_load_sd(&a), _mm_load_sd(&b)));
}

Point3 get_center_of_rectangle(const std::array<Point3, 4>& corners);

inline json vec_to_json(const Vector3& vec) {
  json res;
  res["x"] = vec.x;
  res["y"] = vec.y;
  res["z"] = vec.z;
  return res;
}

inline Vector3 vec_from_json(const json& json_obj) {
  return Vector3(json_obj["x"], json_obj["y"], json_obj["z"]);
}