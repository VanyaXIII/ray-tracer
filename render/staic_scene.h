#pragma once
#include <vector>

#include "camera.h"
#include "colored_plane.h"
#include "colored_sphere.h"
#include "light.h"
#include "pixmap.h"

class StaticScene {
  std::vector<ColoredSphere> spheres_;
  std::vector<ColoredPlane> planes_;
  std::vector<Light> lights_;
  Camera camera_;
  Pixmap pixmap_;

public:
  StaticScene(const Camera& camera, const std::vector<ColoredSphere>& spheres, const std::vector<ColoredPlane>& planes, const std::vector<Light>& lights);
  explicit StaticScene(const Camera& camera);

  void add_sphere(const Sphere& sphere);
  void add_sphere(Sphere&& sphere);
  void add_light(const Light&& sphere);
  void add_light(Light&& sphere);

  void trace_rays();
  void save(const std::string& path) const;
};
