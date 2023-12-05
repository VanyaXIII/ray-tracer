#pragma once

#include "colorable.h"
#include "sphere.h"

struct ColoredSphere final : Sphere, Colorable {
  ColoredSphere(const Point3& center, double rad, const Color& color);
};