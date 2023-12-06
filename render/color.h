#pragma once
#include <cstdint>


struct Color {
    double r;
    double g;
    double b;
    Color(int r, int g, int b);
    Color() = default;
    Color& operator*=(double mul);
    Color multiplied(double mul) const;
};
