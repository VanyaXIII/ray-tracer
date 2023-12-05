#include "vector3.h"

#include <cmath>

Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {
}

Vector3::Vector3(const Vector3& vec1, const Vector3& vec2) : x(vec2.x - vec1.x), y(vec2.y - vec1.y),
                                                             z(vec2.z - vec1.z) {
}

double Vector3::length() const {
  return std::sqrt(squared_length());
}

void Vector3::multiply(double mul) {
  x *= mul;
  y *= mul;
  z *= mul;
}

double Vector3::squared_length() const {
  return x * x + y * y + z * x;
}

void Vector3::normalize() {
  auto len = length();
  x /= len;
  y /= len;
  z /= len;
}

Vector3& Vector3::operator+=(const Vector3& other) {
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

Vector3& Vector3::operator-=(const Vector3& other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
  return *this;
}

double dot_product(const Vector3& vec1, const Vector3& vec2) {
  return vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z;
}
