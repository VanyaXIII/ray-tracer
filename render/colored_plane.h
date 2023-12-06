#pragma once
#include "plane.h"
#include "renderable.h"

struct ColoredPlane final : Plane, Renderable{
  ColoredPlane(const Point3& point1, const Point3& point2, const Point3& point3, const Color& color);
  ColoredPlane(const Point3& point, const Point3& normal, const Color& color);
  Vector3 normal(const Point3& point) const override;
};
