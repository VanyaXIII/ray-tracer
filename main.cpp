
#include <chrono>
#include <iostream>

#include "camera.h"
#include "scene.h"

int main() {

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* win =
    SDL_CreateWindow(
    "Ray Tracer",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    600, 400, SDL_WINDOW_SHOWN);

  Camera camera(600, 400, Point3(-10., 0., 0.),  {Point3(1, 1.5, 1), Point3(1, -1.5, 1), Point3(1, 1.5, -1), Point3{1, -1.5, -1}});
  ColoredSphere sphere1(Point3(5, 0., 0.2), 0.5, Color(0, 0, 255));
  ColoredSphere sphere2(Point3(5, 1, 0.5), 0.5, Color(255, 255, 255));
  ColoredSphere sphere4(Point3(6, -0.7, 0.4), 0.2, Color(128, 128, 255));
  ColoredPlane plane(Point3(7, 0, 0), Vector3(-1, 1, 0), Color(127, 199, 255));
  ColoredPlane plane1(Point3(7, 0, 0), Vector3(-1, -1, 0), Color(255, 0, 255));
  ColoredPlane plane2(Point3(5, 0,-0.5), Vector3(0.1, 0, -1), Color(0, 120, 25));
  Light light1({0, -1, 100}, 1);
  Light light2({0, 1, 0.1}, 0.1);
  Light light3({0, 0, 0.2}, 0.1);
  DynamicScene scene(camera, {sphere1, sphere2, sphere4}, {plane, plane1, plane2}, {light1, light2, light3}, win);
  while (true) {
    SDL_Event event;
    SDL_PollEvent(&event);
    scene.trace_rays();
    scene.move_camera(Vector3(0.02, 0, 0.0));
  }
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
