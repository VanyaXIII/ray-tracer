#include "color.h"

Color::Color(int r, int g, int b) : r(r), g(g), b(b) {
}

Color& Color::operator*=(double mul) {
  r *= mul;
  g *= mul;
  b *= mul;
  return *this;
}

Color Color::multiplied(double mul) const {
  Color res(*this);
  res *= mul;
  return res;
}
