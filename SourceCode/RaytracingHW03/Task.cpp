#include <cmath>
#include <fstream>
#include <iostream>

/// Output image resolution
static const int imageWidth = 800;
static const int imageHeight = 600;
static const int maxColorComponent = 255;

double vectorLength(double x, double y, double z) {
  return sqrt(x * x + y * y + z * z);
}

int main() {
  std::ofstream ppmFileStream("HW03Task01.ppm", std::ios::out | std::ios::binary);

  ppmFileStream << "P3\n"
                << imageWidth << ' ' << imageHeight << '\n'
                << maxColorComponent << '\n';
  for (int rowIdx = 0; rowIdx < imageHeight; ++rowIdx) {
    for (int colIdx = 0; colIdx < imageWidth; ++colIdx) {
      double x = colIdx + 0.5;
      double y = rowIdx + 0.5;
      x /= imageWidth;
      y /= imageHeight;
      x = (2.0 * x) - 1.0;
      y = 1.0 - (2.0 * y);
      x *= imageWidth / imageHeight;
      double length = vectorLength(x, y, -1.0);
      x /= length;
      y /= length;
      double z = -1.0 / length;
      ppmFileStream << abs(x * 255) << ' ' << abs(y * 255) << ' ' << abs(z * 255) << ' ';
    }
    ppmFileStream << '\n';
  }
  ppmFileStream.close();
  return 0;
}