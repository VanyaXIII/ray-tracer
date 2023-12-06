#pragma once
#include <cstdint>


struct Color {
    double r;
    double g;
    double b;
    Color(int r, int g, int b);
    Color() = default;
    Color multiplied(double mul) const;
};
