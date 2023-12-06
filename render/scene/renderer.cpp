#include "renderer.h"

Renderer::Renderer(SDL_Window* win, const std::shared_ptr<Scene>& scene) : renderer_(
                                                                             SDL_CreateRenderer(
                                                                               win, -1, SDL_RENDERER_ACCELERATED)),
                                                                           scene_(scene) {
}

void Renderer::render_frame() const {
  for (size_t i = 0; i < scene_->pixmap().get_height(); ++i) {
    for (size_t j = 0; j < scene_->pixmap().get_width(); ++j) {
      SDL_SetRenderDrawColor(renderer_, static_cast<int>(scene_->pixmap().get(i, j).r),
                             static_cast<int>(scene_->pixmap().get(i, j).g),
                             static_cast<int>(scene_->pixmap().get(i, j).b), 255);
      SDL_RenderDrawPoint(renderer_, j, i);
    }
  }
  SDL_RenderPresent(renderer_);
}
