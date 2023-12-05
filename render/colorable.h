#pragma once
#include "color.h"

struct Colorable {
  Color color;
  Colorable() = default;
  explicit Colorable(const Color& color);
  virtual ~Colorable() = default;
};
