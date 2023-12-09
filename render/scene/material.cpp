#include "material.h"

#include "utils/compare.h"
#include "utils/utils.h"

Color::Color(int r, int g, int b) : r(r), g(g), b(b) {
}

Color Color::multiplied(double mul) const {
  Color res(*this);
  res.r *= mul;
  res.g *= mul;
  res.b *= mul;
  return res;
}

bool operator==(const Color& color1, const Color& color2) {
  return equal(color1.r, color2.r) && equal(color1.g, color2.g) && equal(color1.b, color2.b);
}

Color operator+(const Color& color1, const Color& color2) {
  Color res(color1);
  res.r += color2.r;
  res.g += color2.g;
  res.b += color2.b;
  if (res.r >= 255) {
    res.r = 255;
  }
  if (res.g >= 255) {
    res.g = 255;
  }
  if (res.b >= 255) {
    res.b = 255;
  }
  return res;
}

Material::Material(const Color& diffuse_color, const Vector3& albedo,
                   double spec_exp) : diffuse_color(diffuse_color), albedo(albedo), spec_exp(spec_exp) {
}

Material::Material() : diffuse_color(), albedo({1, 0, 0}), spec_exp(0) {
}

json Material::to_json() const {
  json res;
  res["spec_exp"] = spec_exp;
  res["diffuse_color"]["r"] = diffuse_color.r;
  res["diffuse_color"]["g"] = diffuse_color.g;
  res["diffuse_color"]["b"] = diffuse_color.b;
  res["albedo"] = vec_to_json(albedo);
  return res;
}

Material material_from_json(const json& json_obj) {
  Color color;
  color.r = json_obj["diffuse_color"]["r"];
  color.g = json_obj["diffuse_color"]["g"];
  color.b = json_obj["diffuse_color"]["b"];
  return Material(color, vec_from_json(json_obj["albedo"]), json_obj["spec_exp"]);
}
