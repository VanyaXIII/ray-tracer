//
// Created by ivan on 12/6/23.
//

#include "plane.h"

Plane::Plane(const Vector3& normal, const Point3& point) : normal(normal.normalized()), point(point),
                                                           coef_val(
                                                             -this->normal.x * point.x - this->normal.y * point.y - this->normal.z * point
                                                             .z) {
}

Plane::Plane(const Point3& point1, const Point3& point2, const Point3& point3) :
  normal(cross_product(point2 - point1, point3 - point1).normalize()), point(point1), coef_val(
    -normal.x * point.x - normal.y * point.y - normal.z * point
    .z) {
}
