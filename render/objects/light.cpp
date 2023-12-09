#include "light.h"

#include "utils/utils.h"

Light::Light(const Point3& position, double intensity) : posiiton(position), instensity(intensity){
}

json Light::to_json() const {
  json res;
  res["point"] = vec_to_json(posiiton);
  res["intensity"] = instensity;
  return res;
}

Light light_from_json(const json& json_obj) {
  return Light(vec_from_json(json_obj["point"]), json_obj["intensity"]);
}
