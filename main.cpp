
#include "camera.h"
#include "sphere.h"
#include "staic_scene.h"

int main() {
  Camera camera(600, 400, Point3(-40., 0., 0.),  {Point3(1, 1.5, 1), Point3(1, -1.5, 1), Point3(1, 1.5, -1), Point3{1, -1.5, -1}});
  ColoredSphere sphere1(Point3(5, 0., 0.), 1, Color(255, 0, 0));
  ColoredSphere sphere2(Point3(10, 2, 0.), 0.5, Color(0, 0, 255));
  StaticScene scene(camera, {sphere1, sphere2});
  scene.trace_rays();
  scene.save("../test.ppm");
  int t = 1;
  return 0;
}
