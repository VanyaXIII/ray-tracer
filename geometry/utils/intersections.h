#pragma once

#include "objects/plane.h"
#include "objects/ray.h"
#include "objects/sphere.h"

bool sphere_ray_intersection(const Sphere& sphere, const Ray& ray, double& res);
bool plane_ray_intersection(const Plane& plane, const Ray& ray, double& res);