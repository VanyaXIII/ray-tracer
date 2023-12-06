#pragma once
#include "color.h"
#include "ray.h"
#include "vector3.h"

struct Renderable {
  Color color;
  Renderable() = default;
  explicit Renderable(const Color& color);
  virtual Vector3 normal(const Point3& point) const = 0;
  virtual ~Renderable() = default;
};
