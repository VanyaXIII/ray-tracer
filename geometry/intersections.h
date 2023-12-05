#pragma once
#include <utility>

#include "ray.h"
#include "sphere.h"

std::pair<double, double> sphere_ray_intersection(const Sphere& sphere, const Ray& ray);