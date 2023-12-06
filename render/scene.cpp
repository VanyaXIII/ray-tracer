#include <float.h>

#include "compare.h"
#include "intersections.h"
#include "scene.h"


Scene::Scene(const Camera& camera, const std::vector<ColoredSphere>& spheres,
             const std::vector<ColoredPlane>& planes, const std::vector<Light>& lights) : spheres_(spheres),
  planes_(planes),
  lights_(lights),
  camera_(camera) {
}

Scene::Scene(const Camera& camera) : camera_(camera) {
}

bool Scene::check_intersections(const Ray& ray, double shift) const {
  double val;
  for (const auto& sphere : spheres_) {
    if (sphere_ray_intersection(sphere, ray, val) && is_less(val, shift)) {
      return true;
    }
  }
  for (const auto& plane : planes_) {
    if (plane_ray_intersection(plane, ray, val) && is_less(val, shift)) {
      return true;
    }
  }
  return false;
}

bool Scene::trace_ray(size_t i, size_t j, Color& color) const {
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
    return false;
  }
  Point3 intersection_point = camera_.rays()[i * camera_.width() + j].get_point_by_shift(res);
  double intensity = 0.;
  for (const auto& light : lights_) {
    auto normal = obj->normal(intersection_point);
    if (is_greater(dot_product(camera_.rays()[i * camera_.width() + j].vect, normal), 0.)) {
      normal.multiply(-1);
    }
    auto dot_val = dot_product(normal, (light.posiiton - intersection_point).normalize());
    if (dot_val > 0.) {
      auto direction_vec = light.posiiton - intersection_point;
      Ray check_ray(intersection_point + normal.multiplied(eps), direction_vec);
      if (!check_intersections(check_ray, direction_vec.length())) {
        intensity += light.instensity * dot_val;
      }
    }
  }

  intensity = std::min(intensity, 1.);
  color = obj->color.multiplied(intensity);
  return true;
}

void Scene::move_camera(const Vector3& movement) {
  camera_.move(movement);
}

void StaticScene::trace_rays() {
#pragma omp parallel for schedule(dynamic,1) num_threads(12)
  for (size_t i = 0; i < pixmap_.get_height(); ++i) {
    for (size_t j = 0; j < pixmap_.get_width(); ++j) {
      Color color;
      if (trace_ray(i, j, color)) {
        pixmap_.set(i, j, color);
      }
    }
  }
}

void StaticScene::save(const std::string& path) const {
  pixmap_.write_to_ppm(path);
}

void DynamicScene::trace_rays() {
#pragma omp parallel for schedule(dynamic,1) num_threads(12)
  for (size_t i = 0; i < camera().height(); ++i) {
    for (size_t j = 0; j < camera().width(); ++j) {
      Color color;
      if (trace_ray(i, j, color)) {
        if (trace_ray(i, j, color)) {
          pixmap_.set(i, j, color);
        }
      }
    }
  }
  for (size_t i = 0; i < camera().height(); ++i) {
    for (size_t j = 0; j < camera().width(); ++j) {
      SDL_SetRenderDrawColor(renderer_, static_cast<int>(pixmap_.get(i, j).r), static_cast<int>(pixmap_.get(i, j).g),
                             static_cast<int>(pixmap_.get(i, j).b), 255);
      SDL_RenderDrawPoint(renderer_, j, i);
    }
  }
  SDL_RenderPresent(renderer_);
}


DynamicScene::DynamicScene(const Camera& camera, const std::vector<ColoredSphere>& spheres,
                           const std::vector<ColoredPlane>& planes, const std::vector<Light>& lights,
                           SDL_Window* win) : Scene(
                                                camera, spheres, planes, lights),
                                              renderer_(SDL_CreateRenderer(
                                                win, -1, SDL_RENDERER_ACCELERATED)),
                                              pixmap_(camera.height(), camera.width(), Color(0, 0, 0)) {
}

DynamicScene::DynamicScene(const Camera& camera, SDL_Window* win) : Scene(camera), renderer_(SDL_CreateRenderer(
                                                                      win, -1, SDL_RENDERER_ACCELERATED)),
                                                                    pixmap_(camera.height(), camera.width(),
                                                                            Color(0, 0, 0)) {
}

DynamicScene::~DynamicScene() {
}

const Camera& Scene::camera() const {
  return camera_;
}

StaticScene::StaticScene(const Camera& camera, const std::vector<ColoredSphere>& spheres,
                         const std::vector<ColoredPlane>& planes,
                         const std::vector<Light>& lights)
  : Scene(camera, spheres, planes, lights), pixmap_(camera.height(), camera.width(), Color(0, 0, 0)) {
}

StaticScene::StaticScene(const Camera& camera)
  : Scene(camera), pixmap_(camera.height(), camera.width(), Color(0, 0, 0)) {
}
