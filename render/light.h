#pragma once
#include "vector3.h"

struct Light {
  Point3 posiiton;
  double instensity;
  Light(const Point3& position, double intensity);
};