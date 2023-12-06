#include "utils.h"

Point3 get_center_of_rectangle(const std::array<Point3, 4>& corners) {
  return corners[0].multiplied(0.25) + corners[1].multiplied(0.25) + corners[2].multiplied(0.25) + corners[3].
    multiplied(0.25);
}
