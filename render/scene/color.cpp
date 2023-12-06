#include "color.h"

Color::Color(int r, int g, int b) : r(r), g(g), b(b) {
}

Color Color::multiplied(double mul) const {
  Color res(*this);
  res.r *= mul;
  res.g *= mul;
  res.b *= mul;
  return res;
}
