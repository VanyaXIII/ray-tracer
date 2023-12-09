#pragma once
#include "utils/vector3.h"

struct Ray {
  Point3 point;
  Vector3 vect;
  Ray(const Point3& point, const Vector3& vect);
  Ray() = default;

  Point3 get_point_by_shift(double t) const;
};
