#include "intersections.h"

#include <cmath>
#include <complex>

#include "compare.h"

std::pair<double, double> sphere_ray_intersection(const Sphere& sphere, const Ray& ray) {
  Point3 point = ray.point - sphere.center;
  double coef = ray.vect.x * point.x + ray.vect.y * point.y + ray.vect.z * point.z;
  double val = coef * coef - point.squared_length() + sphere.rad * sphere.rad;
  double sqrt_val = is_zero(val) ? 0. : std::sqrt(val);
  return std::make_pair(-coef + sqrt_val, -coef + sqrt_val);
}
