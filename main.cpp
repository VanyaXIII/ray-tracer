
#include "camera.h"

int main() {
  Camera camera(200, 200, Point3(0., 0., 0.),  {Point3(1, -1, 1), Point3(1, 1, 1), Point3(1, -1, -1), Point3{1, 1, -1}});
  int t = 1;
  return 0;
}
