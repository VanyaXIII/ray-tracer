#pragma once
#include <vector>

#include "camera.h"
#include "colored_sphere.h"
#include "pixmap.h"

class StaticScene {
  std::vector<ColoredSphere> spheres_;
  Camera camera_;
  Pixmap pixmap_;

public:
  StaticScene(const Camera& camera, const std::vector<ColoredSphere>& spheres);
  void trace_rays();
  void save(const std::string& path) const;
};
