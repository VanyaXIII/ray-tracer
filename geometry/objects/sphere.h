#pragma once
#include "utils/vector3.h"

struct Sphere {
  Point3 center;
  double rad;
  Sphere(const Point3& center, double rad);

  Vector3 get_normal(const Point3& point) const;

  virtual ~Sphere() = default;
};
