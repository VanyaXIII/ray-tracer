#pragma once
#include <cmath>

static constexpr double eps = 1e-6;

inline bool equal(double first, double second) {
  return std::abs(first - second) < eps;
}

inline bool is_zero(double num) {
  return std::abs(num) < eps;
}

inline bool is_greater(double first, double second) {
  return first > second + eps;
}

inline bool is_less(double first, double second) {
  return first + eps < second;
}