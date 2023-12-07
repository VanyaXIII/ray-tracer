#include <chrono>
#include <iostream>
#include <SDL2/SDL.h>

#include "scene/camera.h"
#include "scene/renderer.h"
#include "scene/scene.h"

size_t width = 1500;
size_t height = 1000;

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* win =
    SDL_CreateWindow(
      "Ray Tracer",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      width, height, SDL_WINDOW_SHOWN);

  Material mat1(Color(0, 0, 255), {0.6, 0.6, 0.2}, 20);
  Material mat2(Color(255, 255, 255), {0.8, 0.2, 0.}, 10);
  Material mat3(Color(255, 0, 255), {0.6, 0.3, 0.1}, 100);
  Material mat4(Color(128, 128, 255), {1., 0., 0.1}, 100);
  Material mat5(Color(64, 128, 128), {0.9, 0.9, 0.9}, 1000);

  Camera camera(width, height, Point3(-10., 0., 0.), {
                  Point3(1, 1.5, 1), Point3(1, -1.5, 1), Point3(1, 1.5, -1), Point3{1, -1.5, -1}
                });
  ColoredSphere sphere1(Point3(4.5, 0., 0.2), 0.3, mat2);
  ColoredSphere sphere2(Point3(5., 1, 0.5), 0.5, mat1);
  ColoredPlane plane(Point3(7, 0, 0), Vector3(-1, 1, 0), mat3);
  ColoredPlane plane1(Point3(7, 0, 0), Vector3(-1, -1, 0), mat4);
  ColoredPlane plane2(Point3(5, 0, -0.5), Vector3(0.1, 0, -1), mat5);
  Light light1({0, -1, 200}, 1);
  Light light2({0, 1, 0.1}, 0.3);
  Light light3({0, 0, .5}, 0.2);
  Scene scene(camera, {sphere1, sphere2}, {plane, plane1, plane2}, {light1, light2, light3});
  Renderer renderer(win, std::shared_ptr<Scene>(&scene));
  long long len = 1e3;
  long long i = 0;

  scene.trace_rays();
  scene.pixmap().write_to_ppm("../test.ppm");
  renderer.render_frame();
  while (true) {
    auto t_start = std::chrono::high_resolution_clock::now();
    scene.trace_rays();
    renderer.render_frame();
    auto t_end = std::chrono::high_resolution_clock::now();
    if (i % len == 0) {
      std::cout << std::chrono::duration<double, std::milli>(t_end - t_start).count() << std::endl;
    }
  }
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
