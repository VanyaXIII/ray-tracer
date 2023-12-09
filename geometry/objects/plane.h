#pragma once
#include "utils/vector3.h"

struct Plane {
  Vector3 normal;
  Point3 point;
  double coef_val;

  Plane(const Vector3& normal, const Point3& point);
  Plane(const Point3& point1, const Point3& point2, const Point3& point3);

  virtual ~Plane() = default;
};
