#pragma once
#include <utility>

#include "ray.h"
#include "sphere.h"

bool sphere_ray_intersection(const Sphere& sphere, const Ray& ray, double& res);