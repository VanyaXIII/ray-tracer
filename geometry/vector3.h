#pragma once

struct Vector3 {

    double x;
    double y;
    double z;

    Vector3(double x, double y, double z);
    Vector3(const Vector3& vec1, const Vector3& vec2);
    Vector3() = default;

    double length() const;
    void multiply(double mul);
    Vector3 multiplied(double mul) const;
    double squared_length() const;
    Vector3& normalize();
    Vector3 normalized() const;

    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
};

using Point3 = Vector3;

Vector3 operator-(Vector3 first, const Vector3& second);
Vector3 operator+(Vector3 first, const Vector3& second);

double dot_product(const Vector3& vec1, const Vector3& vec2);
Vector3 cross_product(const Vector3& vec1, const Vector3& vec2);
