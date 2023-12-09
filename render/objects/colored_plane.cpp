#include "colored_plane.h"

#include "utils/utils.h"

ColoredPlane::ColoredPlane(const Point3& point1, const Point3& point2, const Point3& point3,
                           const Material& material) : Plane(point1, point2, point3), Renderable(material) {
}

ColoredPlane::ColoredPlane(const Point3& point, const Point3& normal, const Material& material) : Plane(normal, point),
  Renderable(material) {
}

Vector3 ColoredPlane::normal(const Point3& point) const {
  return Plane::normal;
}

json ColoredPlane::to_json() const {
  json res;
  res["point"] = vec_to_json(point);
  res["normal"] = vec_to_json(Plane::normal);
  res["material"] = material.to_json();
  return res;
}

ColoredPlane plane_from_json(const json& json_obj) {
  return ColoredPlane(vec_from_json(json_obj["point"]), vec_from_json(json_obj["normal"]),
                      material_from_json(json_obj["material"]));
}
