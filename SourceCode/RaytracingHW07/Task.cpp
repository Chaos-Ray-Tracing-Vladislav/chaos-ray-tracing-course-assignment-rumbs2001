#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "./lib/camera.hpp"
#include "./lib/ray.hpp"
#include "./lib/scene.hpp"
#include "./lib/triangle.hpp"
#include "./lib/vector.hpp"

void raytracing(Scene& scene, std::string name) {
  std::ofstream ppmFileStream(name, std::ios::out | std::ios::binary);
  ppmFileStream << "P3\n"
                << scene.getSettings().imageWidth << ' ' << scene.getSettings().imageHeight << '\n'
                << maxColorComponent << '\n';

  for (int rowIdx = 0; rowIdx < scene.getSettings().imageHeight; ++rowIdx) {
    for (int colIdx = 0; colIdx < scene.getSettings().imageWidth; ++colIdx) {
      Ray tracingRay(scene.getCamera().getProjectedVector(colIdx, rowIdx, scene.getSettings().imageWidth, scene.getSettings().imageHeight));
      bool isIntersected = false;
      for (int i = 0; i < scene.getGeometryObjects().size(); ++i) {
        if (scene.getGeometryObjects()[i].isIntersected(tracingRay)) {
          isIntersected = true;
          break;
        }
      }
      if (isIntersected) {
        ppmFileStream << "255 255 255 ";
      } else {
        ppmFileStream << scene.getSettings().backgroundColor << ' ';
      }
    }
    ppmFileStream << '\n';
  }
  ppmFileStream.close();
}

int main() {
  Scene scene0("./scenes/scene0.crtscene");
  raytracing(scene0, "HW07Task00.ppm");
  // Scene scene1("./scenes/scene1.crtscene");
  // raytracing(scene0, "HW07Task01.ppm");
  // Scene scene2("./scenes/scene2.crtscene");
  // raytracing(scene2, "HW07Task02.ppm");
  // Scene scene3("./scenes/scene3.crtscene");
  // raytracing(scene3, "HW07Task03.ppm");
  // Scene scene4("./scenes/scene4.crtscene");
  // raytracing(scene4, "HW07Task04.ppm");
  return 0;
}