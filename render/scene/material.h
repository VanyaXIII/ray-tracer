#pragma once
#include <utility>

#include "utils/vector3.h"


struct Color {
    double r;
    double g;
    double b;
    Color(int r, int g, int b);
    Color() = default;
    Color multiplied(double mul) const;
};

bool operator==(const Color& color1, const Color& color2);
Color operator+(const Color& color1, const Color& color2);

struct Material {
    Color diffuse_color;
    Vector3 albedo;
    double spec_exp;
    Material(const Color& diffuse_color, const Vector3& albedo, double spec_exp);
    Material();
};