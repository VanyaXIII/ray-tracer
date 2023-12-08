#include "colored_sphere.h"

#include "utils/utils.h"

ColoredSphere::ColoredSphere(const Point3& center, double rad, const Material& material) : Sphere(center, rad),
  Renderable(material) {
}

Vector3 ColoredSphere::normal(const Point3& point) const {
  return get_normal(point);
}

json ColoredSphere::to_json() const {
  json res;
  res["material"] = material.to_json();
  res["center"] = vec_to_json(center);
  res["rad"] = rad;
  return res;
}

ColoredSphere sphere_from_json(const json& json_obj) {
  return ColoredSphere(vec_from_json(json_obj["center"]), json_obj["rad"], material_from_json(json_obj["material"]));
}
