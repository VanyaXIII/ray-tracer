#pragma once

#include <fstream>
#include <nlohmann/json.hpp>

using namespace nlohmann;

inline void write_json(const json& json_obj, const std::string& path) {
  std::ofstream out(path);
  out << json_obj.dump(4);
  out.close();
}