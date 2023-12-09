#pragma once

#include "scene/material.h"
#include "utils/vector3.h"
#include <nlohmann/json.hpp>

using namespace nlohmann;

struct Renderable {
  Material material;
  Renderable() = default;
  explicit Renderable(const Material& material);
  virtual Vector3 normal(const Point3& point) const = 0;
  virtual ~Renderable() = default;
  virtual json to_json() const = 0;
};