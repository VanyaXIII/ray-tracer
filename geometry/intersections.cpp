#include "intersections.h"

#include <cmath>
#include <complex>
#include <iostream>

#include "compare.h"

bool sphere_ray_intersection(const Sphere& sphere, const Ray& ray, double& res) {
  Point3 point = ray.point - sphere.center;
  double coef = ray.vect.x * point.x + ray.vect.y * point.y + ray.vect.z * point.z;
  double val = coef * coef - point.squared_length() + sphere.rad * sphere.rad;
  if (is_less(val, 0)) {
    return false;
  }
  double sqrt_val = is_zero(val) ? 0. : std::sqrt(val);
  double res1 = -coef - sqrt_val;
  double res2 = -coef + sqrt_val;
  if (is_less(res1, 0)) {
    if (is_less(res2, 0)) {
      return false;
    }
    res = res2;
    return true;
  }
  res = res1;
  return true;
}
