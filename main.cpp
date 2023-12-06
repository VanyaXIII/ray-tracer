
#include "camera.h"
#include "staic_scene.h"

int main() {
  Camera camera(1500, 1000, Point3(-20., 0., 0.),  {Point3(1, 1.5, 1), Point3(1, -1.5, 1), Point3(1, 1.5, -1), Point3{1, -1.5, -1}});
  ColoredSphere sphere1(Point3(5, 0., -0.5), 0.5, Color(0, 0, 255));
  ColoredSphere sphere2(Point3(5, 1, 0.2), 0.5, Color(255, 255, 255));
  ColoredSphere sphere4(Point3(6, -0.5, 0.4), 0.2, Color(128, 128, 0));
  ColoredPlane plane(Point3(7, 0, 0), Vector3(1, 0, 0), Color(127, 199, 255));
  Light light({0, 0., 0}, 1);
  StaticScene scene(camera, {sphere1, sphere2, sphere4}, {plane}, {light});
  scene.trace_rays();
  scene.save("../test.ppm");
  return 0;
}
