
#include <chrono>
#include <iostream>
#include <SDL2/SDL.h>

#include "scene/camera.h"
#include "scene/renderer.h"
#include "scene/scene.h"

int main() {

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* win =
    SDL_CreateWindow(
    "Ray Tracer",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    750, 500, SDL_WINDOW_SHOWN);

  Camera camera(750, 500, Point3(-10., 0., 0.),  {Point3(1, 1.5, 1), Point3(1, -1.5, 1), Point3(1, 1.5, -1), Point3{1, -1.5, -1}});
  ColoredSphere sphere1(Point3(5, 0., 0.2), 0.5, Color(0, 0, 255));
  ColoredSphere sphere2(Point3(5, 1, 0.5), 0.5, Color(255, 255, 255));
  ColoredSphere sphere4(Point3(6, -0.7, 0.4), 0.2, Color(128, 128, 255));
  ColoredPlane plane(Point3(7, 0, 0), Vector3(-1, 1, 0), Color(127, 199, 255));
  ColoredPlane plane1(Point3(7, 0, 0), Vector3(-1, -1, 0), Color(255, 0, 255));
  ColoredPlane plane2(Point3(5, 0,-0.5), Vector3(0.1, 0, -1), Color(0, 120, 25));
  Light light1({0, -1, 100}, 1);
  Light light2({0, 1, 0.1}, 0.1);
  Light light3({0, 0, 0.2}, 0.1);
  Scene scene(camera, {sphere1, sphere2, sphere4}, {plane, plane1, plane2}, {light1, light2, light3});
  Renderer renderer(win, std::shared_ptr<Scene>(&scene));
  long long len = 1e3;
  long long i = 0;

  while (true) {
    auto t_start = std::chrono::high_resolution_clock::now();
    scene.trace_rays();
    renderer.render_frame();
    scene.move_camera(Vector3(0.05, 0, 0.0));
    auto t_end = std::chrono::high_resolution_clock::now();
    if (i % len == 0) {
      std::cout << std::chrono::duration<double, std::milli>(t_end-t_start).count() << std::endl;
    }
  }
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
