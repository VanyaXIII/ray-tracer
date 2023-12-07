#include "colored_plane.h"

ColoredPlane::ColoredPlane(const Point3& point1, const Point3& point2, const Point3& point3, const Material& material) : Plane(point1, point2, point3), Renderable(material) {}

ColoredPlane::ColoredPlane(const Point3& point, const Point3& normal, const Material& material) : Plane(normal, point), Renderable(material) {
}

Vector3 ColoredPlane::normal(const Point3& point) const {
  return Plane::normal;
}
