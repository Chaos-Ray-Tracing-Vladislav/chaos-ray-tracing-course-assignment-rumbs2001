#include <stdlib.h>
#include <time.h>

#include <fstream>
#include <iostream>

/// Output image resolution
static const int imageWidth = 800;
static const int imageHeight = 600;
static const int maxColorComponent = 255;

int min(int x, int y) {
  return x < y ? x : y;
}

int main() {
  srand(time(NULL));

  std::ofstream ppmFileStream("HW02Task01.ppm", std::ios::out | std::ios::binary);

  int rectangles = 4;
  int rowDivision = imageWidth / rectangles, colDivision = imageHeight / rectangles;

  ppmFileStream << "P3\n"
                << imageWidth << ' ' << imageHeight << '\n'
                << maxColorComponent << '\n';
  for (int rowIdx = 0; rowIdx < imageHeight; ++rowIdx) {
    for (int colIdx = 0; colIdx < imageWidth; ++colIdx) {
      int mainRow = rowIdx / colDivision, mainCol = colIdx / rowDivision;
      int sum = (mainRow * rectangles + mainCol) % 6 + 1;
      ppmFileStream << min((rand() % 255 + ((sum & 1) >> 0) * 255), 255) << ' ';
      ppmFileStream << min((rand() % 255 + ((sum & 2) >> 1) * 255), 255) << ' ';
      ppmFileStream << min((rand() % 255 + ((sum & 4) >> 2) * 255), 255) << ' ';
    }
    ppmFileStream << '\n';
  }
  ppmFileStream.close();
  return 0;
}