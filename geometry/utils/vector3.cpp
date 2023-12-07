#include "vector3.h"

#include <cmath>

#include "utils.h"

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

Vector3 Vector3::multiplied(double mul) const {
  Vector3 res(*this);
  res.x *= mul;
  res.y *= mul;
  res.z *= mul;
  return res;
}

double Vector3::squared_length() const {
  return x * x + y * y + z * z;
}

Vector3& Vector3::normalize() {
  auto len = length();
  x /= len;
  y /= len;
  z /= len;
  return *this;
}

Vector3 Vector3::normalized() const {
  Vector3 res(*this);
  return res.normalize();
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

Vector3 operator-(Vector3 first, const Vector3& second) {
  return first -= second;
}

Vector3 operator+(Vector3 first, const Vector3& second) {
  return first += second;
}

double dot_product(const Vector3& vec1, const Vector3& vec2) {
  return fma(vec1.x, vec2.x, fma(vec1.y, vec2.y, fma(vec1.z, vec2.z, 0.)));
}

Vector3 cross_product(const Vector3& vec1, const Vector3& vec2) {
  return Vector3(vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x);
}

Vector3 reflect(const Vector3& vec, const Vector3& normal) {
  return vec - normal.multiplied(2. * dot_product(normal, vec));
}
