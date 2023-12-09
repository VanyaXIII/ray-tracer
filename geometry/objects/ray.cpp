//
// Created by ivan on 12/5/23.
//

#include "ray.h"

Ray::Ray(const Point3& point, const Vector3& vect) : point(point), vect(vect.normalized()) {
}

Point3 Ray::get_point_by_shift(double t) const {
  return point + vect.multiplied(t);
}
