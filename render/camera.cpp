#include "camera.h"

#include "utils.h"

Camera::Camera(size_t width, size_t height, const Point3& focus, const std::array<Point3, 4>& corners) :
  height_(height), width_(width), focus_(focus), normal_(get_center_of_rectangle(corners)),
  rays_(height * width) {
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

size_t Camera::width() const {
  return width_;
}

const std::vector<Ray>& Camera::rays() const {
  return rays_;
}

size_t Camera::height() const {
  return height_;
}

