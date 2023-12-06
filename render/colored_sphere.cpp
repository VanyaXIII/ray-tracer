#include "colored_sphere.h"

ColoredSphere::ColoredSphere(const Point3& center, double rad, const Color& color) : Sphere(center, rad),
  Renderable(color) {
}
