#pragma once

#include "renderable.h"
#include "objects/sphere.h"

struct ColoredSphere final : Sphere, Renderable {
  ColoredSphere(const Point3& center, double rad, const Material& material);
  Vector3 normal(const Point3& point) const override;
  json to_json() const override;
};

ColoredSphere sphere_from_json(const json& json_obj);