#pragma once
#include "vector3.h"

struct Sphere {
  Point3 center;
  double rad;
  Sphere(const Point3& center, double rad);

  virtual ~Sphere() = default;
};
