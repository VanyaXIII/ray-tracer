#pragma once

#include "scene/material.h"
#include "utils/vector3.h"

struct Renderable {
  Material material;
  Renderable() = default;
  explicit Renderable(const Material& material);
  virtual Vector3 normal(const Point3& point) const = 0;
  virtual ~Renderable() = default;
};
