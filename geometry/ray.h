#pragma once
#include "vector3.h"

class Ray {
  Point3 point;
  Vector3 vect;

public:
  Ray(const Point3& point, const Vector3& vect);
};
