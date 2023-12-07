#pragma once
#include "objects/plane.h"
#include "renderable.h"

struct ColoredPlane final : Plane, Renderable{
  ColoredPlane(const Point3& point1, const Point3& point2, const Point3& point3, const Material& material);
  ColoredPlane(const Point3& point, const Point3& normal, const Material& material);
  Vector3 normal(const Point3& point) const override;
};
