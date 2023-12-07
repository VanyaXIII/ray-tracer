#include "colored_sphere.h"

ColoredSphere::ColoredSphere(const Point3& center, double rad, const Material& material) : Sphere(center, rad),
  Renderable(material) {
}

Vector3 ColoredSphere::normal(const Point3& point) const {
  return get_normal(point);
}
