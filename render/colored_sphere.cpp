#include "colored_sphere.h"

ColoredSphere::ColoredSphere(const Point3& center, double rad, const Color& color) : Sphere(center, rad),
  Renderable(color) {
}

Vector3 ColoredSphere::normal(const Point3& point) const {
  return get_normal(point);
}
