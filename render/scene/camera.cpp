#include "camera.h"

#include "utils/utils.h"

Camera::Camera(size_t width, size_t height, const Point3& focus, const std::array<Point3, 4>& corners) :
  height_(height), width_(width), focus_(focus), normal_(get_center_of_rectangle(corners)),
  rays_(height * width), corners_(corners) {
  Vector3 vec1 = corners[1] - corners[0];
  vec1.multiply(1. / (width - 1));
  Vector3 vec2 = corners[2] - corners[0];
  vec2.multiply(1. / (height - 1));
  Point3 current = corners[0];
  for (size_t i = 0; i < height_; ++i) {
    for (size_t j = 0; j < width_; ++j) {
      rays_[i * width_ + j] = Ray(focus_, Vector3(focus_, current));
      current += vec1;
    }
    current = corners[0] + vec2.multiplied(i + 1);
  }
}

void Camera::move(const Vector3& movement) {
  for (auto& ray : rays_) {
    ray.point += movement;
  }
  focus_ += movement;
}

size_t Camera::width() const {
  return width_;
}

const std::vector<Ray>& Camera::rays() const {
  return rays_;
}

json Camera::to_json() const {
  json res;
  res["focus"] = vec_to_json(focus_);
  res["width"] = width_;
  res["height"] = height_;
  for (size_t i = 0; i < 4; ++i) {
    res["corners"][i] = vec_to_json(corners_[i]);
  }
  return res;
}

Camera camera_from_json(const json& json_obj) {
  std::array<Point3, 4> corners;
  for (size_t i = 0; i < 4; ++i) {
    corners[i] = vec_from_json(json_obj["corners"][i]);
  }
  return Camera(json_obj["width"], json_obj["height"], vec_from_json(json_obj["focus"]), corners);
}

size_t Camera::height() const {
  return height_;
}
