#include <algorithm>
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

void raytracing(Scene &scene, std::string name) {
  std::ofstream ppmFileStream(name, std::ios::out | std::ios::binary);
  ppmFileStream << "P3\n"
                << scene.getSettings().imageWidth << ' ' << scene.getSettings().imageHeight << '\n'
                << maxColorComponent << '\n';

  for (int rowIdx = 0; rowIdx < scene.getSettings().imageHeight; ++rowIdx) {
    for (int colIdx = 0; colIdx < scene.getSettings().imageWidth; ++colIdx) {
      Ray tracingRay(scene.getCamera().getProjectedVector(colIdx, rowIdx, scene.getSettings().imageWidth, scene.getSettings().imageHeight));
      bool isIntersected = false;
      int interindex = -1;
      IntersectionData intersectionData, intersectionDataTemp;
      for (int i = 0; i < scene.getGeometryObjects().size(); ++i) {
        if (scene.getGeometryObjects()[i].intersect(tracingRay, intersectionDataTemp)) {
          if (!isIntersected || intersectionDataTemp.distance < intersectionData.distance) {
            intersectionData = intersectionDataTemp;
          }
          isIntersected = true;
          interindex = i;
        }
      }
      if (isIntersected) {
        Color finalColor;
        for (const Light &light : scene.getLights()) {
          Vector lightDirection(intersectionData.position, light.position);
          double sphereRadius = lightDirection.vectorLength();
          lightDirection.normalize();
          double cosLaw = std::max(0.0, dotProduct(lightDirection, intersectionData.normal));
          double lightIntensity;
          Color albedo(0.9f, 0.9f, 0.9f);
          double sa = 4 * PI * sphereRadius * sphereRadius;
          Ray shadowRay(intersectionData.position + intersectionData.normal * 0.05f, lightDirection);
          bool isIntersectedShadow = false;
          IntersectionData intersectionShadow;
          for (int i = 0; i < scene.getGeometryObjects().size(); ++i) {
            if (scene.getGeometryObjects()[i].intersect(shadowRay, intersectionShadow)) {
              isIntersectedShadow = true;
              break;
            }
          }
          if (!isIntersectedShadow) {
            Color lightContribution = albedo * ((light.intensity / sa) * cosLaw);
            finalColor += lightContribution;
          } else {
          }
        }
        ppmFileStream << finalColor << ' ';
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
  raytracing(scene0, "HW08Task00.ppm");
  // Scene scene1("./scenes/scene1.crtscene");
  // raytracing(scene1, "HW08Task01.ppm");
  // Scene scene2("./scenes/scene2.crtscene");
  // raytracing(scene2, "HW08Task02.ppm");
  // Scene scene3("./scenes/scene3.crtscene");
  // raytracing(scene3, "HW08Task03.ppm");
  return 0;
}