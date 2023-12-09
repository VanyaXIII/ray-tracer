#include "pixmap.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

Pixmap::Pixmap(size_t height, size_t width, const Color& color) : pixels_map_(
  height, std::vector<Color>(width, color)), changed_(height, std::vector<bool>(width, false)) {
  if (height == 0 || width == 0) {
    throw std::runtime_error("Invalid size");
  }
}

Pixmap::Pixmap(size_t height, size_t width) : Pixmap(height, width, Color(0, 0, 0)) {
}

const Color& Pixmap::get(size_t i, size_t j) const {
  changed_[i][j] = false;
  return pixels_map_[i][j];
}

void Pixmap::set(size_t i, size_t j, const Color& color) {
  if (pixels_map_[i][j] == color) {
    return;
  }
  pixels_map_[i][j] = color;
  changed_[i][j] = true;
}

size_t Pixmap::get_width() const {
  return pixels_map_[0].size();
}

size_t Pixmap::get_height() const {
  return pixels_map_.size();
}

std::pair<size_t, size_t> Pixmap::get_shape() const {
  return std::make_pair(pixels_map_.size(), pixels_map_[0].size());
}

void Pixmap::write(std::ostream& out) const {
  out << "P3\n";
  out << get_width() << ' ' << get_height() << '\n';
  out << "255\n";
  for (size_t i = 0; i < pixels_map_.size(); ++i) {
    for (size_t j = 0; j < pixels_map_[0].size(); ++j) {
      out << static_cast<int>(pixels_map_[i][j].r) << ' ' << static_cast<int>(pixels_map_[i][j].g) << ' ' << static_cast
        <int>(pixels_map_[i][j].b) << '\n';
    }
  }
}

void Pixmap::write_to_ppm(const std::string& path) const {
  std::ofstream out(path);
  write(out);
  out.close();
}

void Pixmap::write_to_stdout() const {
  write(std::cout);
}
