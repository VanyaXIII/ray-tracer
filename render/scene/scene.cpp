#include <float.h>

#include "utils/compare.h"
#include "utils/intersections.h"
#include "scene.h"

#include <fstream>

#include "objects/ray.h"


Scene::Scene(const Camera& camera, const std::vector<ColoredSphere>& spheres,
             const std::vector<ColoredPlane>& planes, const std::vector<Light>& lights) : spheres_(spheres),
  planes_(planes),
  lights_(lights),
  camera_(camera),
  pixmap_(camera.height(), camera.width(),
          Color(0, 0, 0)) {
}

Scene::Scene(const Camera& camera) : camera_(camera), pixmap_(camera.height(), camera.width(),
                                                              Color(0, 0, 0)) {
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

bool Scene::trace_ray(const Ray& ray, Color& color, size_t depth) const {
  if (depth > 1000) {
    return false;
  }
  double res;
  Renderable const* obj = find_intersection_object(ray, res);
  if (!obj) {
    return false;
  }
  Point3 intersection_point = ray.get_point_by_shift(res);
  auto normal = obj->normal(intersection_point);
  if (is_greater(dot_product(ray.vect, normal), 0.)) {
    normal.multiply(-1);
  }
  double dif_intensity = 0.;
  double spec_intensity = 0.;
  Point3 start_point = intersection_point + normal.multiplied(eps);
  for (const auto& light : lights_) {
    auto to_light_vec = light.posiiton - intersection_point;
    auto len = to_light_vec.length();
    to_light_vec.normalize();
    Ray check_ray(start_point, to_light_vec);
    if (!check_intersections(check_ray, len)) {
      dif_intensity += light.instensity * std::max(0., dot_product(to_light_vec, normal));
      spec_intensity += light.instensity * pow(
        std::max(0., dot_product(reflect(to_light_vec.multiplied(-1), normal).multiplied(-1), ray.vect)),
        obj->material.spec_exp);
    }
  }

  Ray reflected_ray(start_point, reflect(ray.vect, normal));
  Color reflection_color;
  bool reflection_flag = trace_ray(reflected_ray, reflection_color, depth + 1);

  dif_intensity = std::min(dif_intensity, 1.);
  spec_intensity = std::min(spec_intensity, 1.);
  const Material& material = obj->material;
  color = material.diffuse_color.multiplied(material.albedo.x * dif_intensity) + Color(255, 255, 255).multiplied(
    spec_intensity * material.albedo.y);
  if (reflection_flag) {
    color = color + reflection_color.multiplied(material.albedo.z);
  }
  return true;
}

Renderable const* Scene::find_intersection_object(const Ray& ray, double& shift) const {
  double res = DBL_MAX;
  Renderable const* obj = nullptr;
  for (const auto& sphere : spheres_) {
    double val;
    if (sphere_ray_intersection(sphere, ray, val) && val < res) {
      res = val;
      obj = &sphere;
    }
  }
  for (const auto& plane : planes_) {
    double val;
    bool int_val = plane_ray_intersection(plane, ray, val);
    if (int_val && val < res) {
      res = val;
      obj = &plane;
    }
  }
  shift = res;
  return obj;
}

void Scene::trace_rays() {
#pragma omp parallel for schedule(dynamic,1) num_threads(12)
  for (size_t i = 0; i < pixmap_.get_height(); ++i) {
    for (size_t j = 0; j < pixmap_.get_width(); ++j) {
      Color color;
      if (trace_ray(camera_.rays()[i * camera_.width() + j], color)) {
        pixmap_.set(i, j, color);
      }
    }
  }
}

void Scene::move_camera(const Vector3& movement) {
  camera_.move(movement);
}

const Camera& Scene::camera() const {
  return camera_;
}

const Pixmap& Scene::pixmap() const {
  return pixmap_;
}

json Scene::to_json() const {
  json res;
  for (const auto& sphere : spheres_) {
    res["spheres"].push_back(sphere.to_json());
  }
  for (const auto& plane : planes_) {
    res["planes"].push_back(plane.to_json());
  }
  for (const auto& light : lights_) {
    res["lights"].push_back(light.to_json());
  }
  res["camera"] = camera_.to_json();
  return res;
}

Scene scene_from_json(const json& json_obj) {
  Camera camera = camera_from_json(json_obj["camera"]);
  std::vector<ColoredSphere> spheres;
  std::vector<ColoredPlane> planes;
  std::vector<Light> lights;
  for (const auto& obj : json_obj["planes"]) {
    planes.push_back(plane_from_json(obj));
  }
  for (const auto& obj : json_obj["spheres"]) {
    spheres.push_back(sphere_from_json(obj));
  }
  for (const auto& obj : json_obj["lights"]) {
    lights.push_back(light_from_json(obj));
  }
  return Scene(camera, spheres, planes, lights);
}

Scene read_scene(const std::string& path) {
  std::ifstream in(path);
  json json_obj;
  in >> json_obj;
  return scene_from_json(json_obj);
}
