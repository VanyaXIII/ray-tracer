#include "sphere.h"

Sphere::Sphere(const Point3& center, double rad) : center(center), rad(rad) {
}

Vector3 Sphere::get_normal(const Point3& point) const {
  auto res = point -center;
  res.normalize();
  return res;
}
