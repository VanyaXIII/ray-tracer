#include <float.h>

#include "compare.h"
#include "intersections.h"
#include "staic_scene.h"


StaticScene::StaticScene(const Camera& camera, const std::vector<ColoredSphere>& spheres) : spheres_(spheres),
  camera_(camera),
  pixmap_(camera.height(), camera.width(), Color(0, 0, 0)) {
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
      if (obj) {
        pixmap_.set(i, j, obj->color);
      }
    }
  }
}

void StaticScene::save(const std::string& path) const {
  pixmap_.write_to_ppm(path);
}
