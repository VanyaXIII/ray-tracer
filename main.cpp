#include <iostream>
#include <SDL2/SDL.h>
#include <nlohmann/json.hpp>

#include "scene/camera.h"
#include "scene/renderer.h"
#include "scene/scene.h"
#include "utils.h"

size_t width = 1500;
size_t height = 1000;

using namespace nlohmann::literals;

bool handle_events() {
  SDL_Event event;
  SDL_PollEvent(&event);
  if (event.type == SDL_QUIT) {
    return true;
  }
  return false;
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* win =
    SDL_CreateWindow(
      "Ray Tracer",
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      width, height, SDL_WINDOW_SHOWN);


  auto scene = std::make_shared<Scene>(read_scene("../scene.json"));
  Renderer renderer(win, scene);

  scene->trace_rays();
  renderer.render_frame();

  while (!handle_events()) {}
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
