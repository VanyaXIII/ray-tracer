#pragma once

struct Vector3 {

    double x;
    double y;
    double z;

    Vector3(double x, double y, double z);
    Vector3(const Vector3& vec1, const Vector3& vec2);

    double length() const;
    void multiply(double mul);
    double squared_length() const;
    void normalize();

    Vector3& operator+=(const Vector3& other);
    Vector3& operator-=(const Vector3& other);
};

using Point3 = Vector3;

double dot_product(const Vector3& vec1, const Vector3& vec2);
