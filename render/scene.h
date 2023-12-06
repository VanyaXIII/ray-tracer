#pragma once
#include <memory>
#include <vector>
#include <SDL2/SDL.h>

#include "camera.h"
#include "colored_plane.h"
#include "colored_sphere.h"
#include "light.h"
#include "pixmap.h"

class Scene {
  std::vector<ColoredSphere> spheres_;
  std::vector<ColoredPlane> planes_;
  std::vector<Light> lights_;
  Camera camera_;

protected:
  bool check_intersections(const Ray& ray, double shift) const;
  bool trace_ray(size_t i, size_t j, Color& color) const;

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

  virtual void trace_rays() = 0;
  const Camera& camera() const;
};

class StaticScene final : public Scene {
  Pixmap pixmap_;

public:
  StaticScene(const Camera& camera, const std::vector<ColoredSphere>& spheres, const std::vector<ColoredPlane>& planes,
              const std::vector<Light>& lights);

  explicit StaticScene(const Camera& camera);

  void trace_rays() override;
  void save(const std::string& path) const;
};

class DynamicScene final : public Scene {
public:

  void trace_rays() override;

  DynamicScene(const Camera& camera, const std::vector<ColoredSphere>& spheres, const std::vector<ColoredPlane>& planes,
        const std::vector<Light>& lights, SDL_Window* win);
  explicit DynamicScene(const Camera& camera, SDL_Window* win);

  ~DynamicScene();

private:
  SDL_Renderer* renderer_;
  Pixmap pixmap_;
};
