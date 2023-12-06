#include "colored_plane.h"

ColoredPlane::ColoredPlane(const Point3& point1, const Point3& point2, const Point3& point3, const Color& color) : Plane(point1, point2, point3), Renderable(color) {}

ColoredPlane::ColoredPlane(const Point3& point, const Point3& normal, const Color& color) : Plane(normal, point), Renderable(color) {
}

Vector3 ColoredPlane::normal(const Point3& point) const {
  return Plane::normal;
}
