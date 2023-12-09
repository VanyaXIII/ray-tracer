#pragma once
#include <array>
#include <vector>
#include <nlohmann/json.hpp>

using namespace nlohmann;
using std::size_t;

#include "objects/ray.h"
#include "utils/vector3.h"

class Camera {
  size_t height_;
  size_t width_;
  Point3 focus_;
  Vector3 normal_;
  std::vector<Ray> rays_;
  std::array<Point3, 4> corners_;

public:
  Camera(size_t width, size_t height, const Point3& focus, const std::array<Point3, 4>& corners);

  void move(const Vector3& movement);

  size_t height() const;
  size_t width() const;
  const std::vector<Ray>& rays() const;

  json to_json() const;
};

Camera camera_from_json(const json& json_obj);
