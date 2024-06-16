#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "./lib/camera.hpp"
#include "./lib/ray.hpp"
#include "./lib/triangle.hpp"
#include "./lib/vector.hpp"

void Task01() {
  // Task 01
  std::ofstream ppmFileStream("HW05Task01.ppm", std::ios::out | std::ios::binary);
  ppmFileStream << "P3\n"
                << imageWidth << ' ' << imageHeight << '\n'
                << maxColorComponent << '\n';
  Camera myCamera(Vector(0, 0, 0), Vector(0, 0, -1));
  Triangle myTriangle(Vector(-1.75, -1.75, -3),
                      Vector(1.75, -1.75, -3),
                      Vector(0, 1.75, -3));

  for (int rowIdx = 0; rowIdx < imageHeight; ++rowIdx) {
    for (int colIdx = 0; colIdx < imageWidth; ++colIdx) {
      Ray tracingRay(myCamera.getProjectedVector(colIdx, rowIdx));
      if (myTriangle.intersect(tracingRay)) {
        ppmFileStream << "255 255 255 ";
      } else {
        ppmFileStream << "0 0 0 ";
      }
    }
    ppmFileStream << '\n';
  }
  ppmFileStream.close();
}

void Task02() {
  // Task 02
  std::ofstream ppmFileStream("HW05Task02.ppm", std::ios::out | std::ios::binary);
  ppmFileStream << "P3\n"
                << imageWidth << ' ' << imageHeight << '\n'
                << maxColorComponent << '\n';
  Camera myCamera(Vector(0, 0, 0), Vector(0, 0, -1));
  Triangle myTriangle(Vector(-2, 0, -3),
                      Vector(3, 1, -6),
                      Vector(-1, 2, -9));

  for (int rowIdx = 0; rowIdx < imageHeight; ++rowIdx) {
    for (int colIdx = 0; colIdx < imageWidth; ++colIdx) {
      Ray tracingRay(myCamera.getProjectedVector(colIdx, rowIdx));
      if (myTriangle.intersect(tracingRay)) {
        ppmFileStream << "255 255 255 ";
      } else {
        ppmFileStream << "0 0 0 ";
      }
    }
    ppmFileStream << '\n';
  }
  ppmFileStream.close();
}

void Task03() {
  // Task 03
  std::ofstream ppmFileStream("HW05Task03.ppm", std::ios::out | std::ios::binary);
  ppmFileStream << "P3\n"
                << imageWidth << ' ' << imageHeight << '\n'
                << maxColorComponent << '\n';
  Camera myCamera(Vector(0, 0, 0), Vector(0, 0, -1));
  std::vector<Triangle> triangles;
  triangles.reserve(2);
  triangles.push_back(Triangle(Vector(-1.75, -1.75, -3), Vector(1.75, -1.75, -3), Vector(0, 1.75, -3)));
  triangles.push_back(Triangle(Vector(-2, 0, -3), Vector(3, 1, -6), Vector(-1, 2, -9)));

  for (int rowIdx = 0; rowIdx < imageHeight; ++rowIdx) {
    for (int colIdx = 0; colIdx < imageWidth; ++colIdx) {
      Ray tracingRay(myCamera.getProjectedVector(colIdx, rowIdx));
      bool isIntersected = false;
      for (Triangle const& triangle : triangles) {
        if (triangle.intersect(tracingRay)) {
          isIntersected = true;
          break;
        }
      }
      if (isIntersected) {
        ppmFileStream << "255 255 255 ";
      } else {
        ppmFileStream << "0 0 0 ";
      }
    }
    ppmFileStream << '\n';
  }
  ppmFileStream.close();
}

void Task04() {
  // Task 04
  std::ofstream ppmFileStream("HW05Task04.ppm", std::ios::out | std::ios::binary);
  ppmFileStream << "P3\n"
                << imageWidth << ' ' << imageHeight << '\n'
                << maxColorComponent << '\n';
  Camera myCamera(Vector(0, 0, 0), Vector(0, 0, -1));
  std::vector<Triangle> triangles;
  triangles.reserve(2);
  triangles.push_back(Triangle(Vector(-2.8, 1, -5), Vector(0, -1, -5), Vector(2.8, 1, -5)));
  triangles.push_back(Triangle(Vector(-1.8, -2.4, -3), Vector(1, -0.4, -3), Vector(0, 3, -3)));
  triangles.push_back(Triangle(Vector(-1, -0.4, -4), Vector(1.8, -2.4, -4), Vector(0, 3, -4)));

  for (int rowIdx = 0; rowIdx < imageHeight; ++rowIdx) {
    for (int colIdx = 0; colIdx < imageWidth; ++colIdx) {
      Ray tracingRay(myCamera.getProjectedVector(colIdx, rowIdx));
      bool isIntersected = false;
      for (Triangle const& triangle : triangles) {
        if (triangle.intersect(tracingRay)) {
          isIntersected = true;
          break;
        }
      }
      if (isIntersected) {
        ppmFileStream << "255 255 255 ";
      } else {
        ppmFileStream << "0 0 0 ";
      }
    }
    ppmFileStream << '\n';
  }
  ppmFileStream.close();
}

int main() {
  Task01();
  Task02();
  Task03();
  Task04();
  return 0;
}