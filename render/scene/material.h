#pragma once
#include <nlohmann/json.hpp>

#include "utils/vector3.h"

using namespace nlohmann;

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
    json to_json() const;
};

Material material_from_json(const json& json_obj);