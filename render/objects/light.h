#pragma once
#include <nlohmann/json.hpp>

#include "utils/vector3.h"

using namespace nlohmann;

struct Light {
  Point3 posiiton;
  double instensity;
  Light(const Point3& position, double intensity);

  json to_json() const;
};

Light light_from_json(const json& json_obj);
