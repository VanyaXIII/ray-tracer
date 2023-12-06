#pragma once
#include <memory>
#include <SDL_render.h>

#include "scene.h"

class Renderer {
  SDL_Renderer* renderer_;
  std::shared_ptr<Scene> scene_;

public:
  Renderer(SDL_Window* win, const std::shared_ptr<Scene>& scene);
  void render_frame() const;
};
