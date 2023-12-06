#include <float.h>

#include "compare.h"
#include "intersections.h"
#include "staic_scene.h"


StaticScene::StaticScene(const Camera& camera, const std::vector<ColoredSphere>& spheres,
                         const std::vector<ColoredPlane>& planes, const std::vector<Light>& lights) : spheres_(spheres),
  planes_(planes),
  lights_(lights),
  camera_(camera),
  pixmap_(camera.height(), camera.width(), Color(0, 0, 0)) {
}

StaticScene::StaticScene(const Camera& camera) : camera_(camera),
                                                 pixmap_(camera_.height(), camera_.width(), Color(0, 0, 0)) {
}

void StaticScene::trace_rays() {
  for (size_t i = 0; i < camera_.height(); ++i) {
    for (size_t j = 0; j < camera_.width(); ++j) {
      double res = DBL_MAX;
      Renderable const* obj = nullptr;
      for (const auto& sphere : spheres_) {
        double val;
        if (sphere_ray_intersection(sphere, camera_.rays()[i * camera_.width() + j], val) && val < res) {
          res = val;
          obj = &sphere;
        }
      }
      for (const auto& plane : planes_) {
        double val;
        if (plane_ray_intersection(plane, camera_.rays()[i * camera_.width() + j], val) && val < res) {
          res = val;
          obj = &plane;
        }
      }
      if (!obj) {
        continue;
      }
      Point3 intersection_point = camera_.rays()[i * camera_.width() + j].get_point_by_shift(res);
      double intensity = 0.;
      for (const auto& light : lights_) {
        auto normal = obj->normal(intersection_point);
        if (is_greater(dot_product(camera_.rays()[i * camera_.width() + j].vect, normal), 0.)) {
          normal.multiply(-1);
        }
        intensity += light.instensity * std::max(0., dot_product(normal,
                                                                 (light.posiiton - intersection_point).normalize()));
      }
      intensity = std::min(intensity, 1.);
      pixmap_.set(i, j, obj->color.multiplied(intensity));
    }
  }
}

void StaticScene::save(const std::string& path) const {
  pixmap_.write_to_ppm(path);
}
