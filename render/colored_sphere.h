#pragma once

#include "renderable.h"
#include "sphere.h"

struct ColoredSphere final : Sphere, Renderable {
  ColoredSphere(const Point3& center, double rad, const Color& color);
};