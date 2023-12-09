#pragma once
#include <string>
#include <vector>

#include "material.h"

class Pixmap {
  std::vector<std::vector<Color>> pixels_map_;
  mutable std::vector<std::vector<bool>> changed_;

public:
  Pixmap(size_t height, size_t width, const Color& color);
  Pixmap(size_t height, size_t width);

  const Color& get(size_t i, size_t j) const;
  void set(size_t i, size_t j, const Color& color);

  size_t get_width() const;
  size_t get_height() const;
  std::pair<size_t, size_t> get_shape() const;

  void write(std::ostream& out) const;
  void write_to_ppm(const std::string& path) const;
  void write_to_stdout() const;
};