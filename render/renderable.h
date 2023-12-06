#pragma once
#include "color.h"

struct Renderable {
  Color color;
  Renderable() = default;
  explicit Renderable(const Color& color);
  virtual ~Renderable() = default;
};
