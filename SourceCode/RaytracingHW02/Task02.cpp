#include <stdlib.h>
#include <time.h>

#include <fstream>
#include <iostream>

/// Output image resolution
static const int imageWidth = 800;
static const int imageHeight = 600;
static const int maxColorComponent = 255;

int main() {
  srand(time(NULL));

  std::ofstream ppmFileStream("HW02Task02.ppm", std::ios::out | std::ios::binary);

  int circleX = 400,
      circleY = 300,
      circleR = 100;
  int circleRSquared = circleR * circleR;

  ppmFileStream << "P3\n"
                << imageWidth << ' ' << imageHeight << '\n'
                << maxColorComponent << '\n';
  for (int rowIdx = 0; rowIdx < imageHeight; ++rowIdx) {
    for (int colIdx = 0; colIdx < imageWidth; ++colIdx) {
      int distanceSquared =
          (circleX - colIdx) * (circleX - colIdx) +
          (circleY - rowIdx) * (circleY - rowIdx);
      if (distanceSquared < circleRSquared) {
        ppmFileStream << "200 0 0 ";
      } else {
        ppmFileStream << "0 0 100 ";
      }
    }
    ppmFileStream << '\n';
  }
  ppmFileStream.close();
  return 0;
}