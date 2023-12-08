#pragma once
#include <memory>
#include <vector>

#include "camera.h"
#include "objects/colored_plane.h"
#include "objects/colored_sphere.h"
#include "objects/light.h"
#include "pixmap.h"
#include "objects/ray.h"
#include "objects/sphere.h"
#include "utils/vector3.h"

class Scene {
  std::vector<ColoredSphere> spheres_;
  std::vector<ColoredPlane> planes_;
  std::vector<Light> lights_;
  Camera camera_;
  Pixmap pixmap_;

protected:
  bool check_intersections(const Ray& ray, double shift) const;
  bool trace_ray(const Ray& ray, Color& color, size_t depth = 0) const;
  Renderable const* find_intersection_object(const Ray& ray, double& shift) const;

public:
  void move_camera(const Vector3& movement);

  virtual ~Scene() = default;

  Scene(const Camera& camera, const std::vector<ColoredSphere>& spheres, const std::vector<ColoredPlane>& planes,
        const std::vector<Light>& lights);
  explicit Scene(const Camera& camera);

  void add_sphere(const Sphere& sphere);
  void add_sphere(Sphere&& sphere);
  void add_light(const Light&& sphere);
  void add_light(Light&& sphere);

  void trace_rays();
  const Camera& camera() const;
  const Pixmap& pixmap() const;

  json to_json() const;
};

Scene scene_from_json(const json& json_obj);
Scene read_scene(const std::string& path);
