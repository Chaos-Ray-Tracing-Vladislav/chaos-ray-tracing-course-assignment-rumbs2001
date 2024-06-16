#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "./lib/camera.hpp"
#include "./lib/ray.hpp"
#include "./lib/triangle.hpp"
#include "./lib/vector.hpp"

void Task01() {  // Task01
  std::ofstream ppmFileStream("HW06Task01.ppm", std::ios::out | std::ios::binary);
  ppmFileStream << "P3\n"
                << imageWidth << ' ' << imageHeight << '\n'
                << maxColorComponent << '\n';

  Camera myCamera;
  myCamera.pan(30);

  Triangle myTriangle(Vector(-1.75, -1.75, -3), Vector(1.75, -1.75, -3), Vector(0, 1.75, -3));

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

void Task02() {  // Task02
  std::ofstream ppmFileStream("HW06Task02.ppm", std::ios::out | std::ios::binary);
  ppmFileStream << "P3\n"
                << imageWidth << ' ' << imageHeight << '\n'
                << maxColorComponent << '\n';

  Camera myCamera;
  myCamera.pedestal(2);
  myCamera.dolly(3);

  Triangle myTriangle(Vector(-1.75, -1.75, -3), Vector(1.75, -1.75, -3), Vector(0, 1.75, -3));

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

void Task03() {  // Task03
  Camera myCamera;
  Triangle myTriangle(Vector(-1.75, -1.75, -3), Vector(1.75, -1.75, -3), Vector(0, 1.75, -3));
  {
    std::ofstream ppmFileStream("HW06Task03_01.ppm", std::ios::out | std::ios::binary);
    ppmFileStream << "P3\n"
                  << imageWidth << ' ' << imageHeight << '\n'
                  << maxColorComponent << '\n';
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
  myCamera.roll(90);
  myCamera.dolly(1.5);
  {
    std::ofstream ppmFileStream("HW06Task03_02.ppm", std::ios::out | std::ios::binary);
    ppmFileStream << "P3\n"
                  << imageWidth << ' ' << imageHeight << '\n'
                  << maxColorComponent << '\n';
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
}

void Task04() {  // Task04
  Camera myCamera;
  Triangle myTriangle(Vector(-1.75, -1.75, -3), Vector(1.75, -1.75, -3), Vector(0, 1.75, -3));
  {
    std::ofstream ppmFileStream("HW06Task04_01.ppm", std::ios::out | std::ios::binary);
    ppmFileStream << "P3\n"
                  << imageWidth << ' ' << imageHeight << '\n'
                  << maxColorComponent << '\n';
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
  myCamera.pedestal(2);
  myCamera.dolly(-2);
  myCamera.pan(30);
  myCamera.tilt(10);
  {
    std::ofstream ppmFileStream("HW06Task04_02.ppm", std::ios::out | std::ios::binary);
    ppmFileStream << "P3\n"
                  << imageWidth << ' ' << imageHeight << '\n'
                  << maxColorComponent << '\n';
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
}

void Task05() {  // Task05
  Camera myCamera;
  myCamera.truck(-5);
  myCamera.pan(20);
  std::vector<Triangle> triangles;
  triangles.push_back(Triangle(Vector(-3, -3, -5), Vector(3, -3, -5), Vector(0, 3, -5)));

  for (int i = 0; i < 20; ++i) {
    char value[5];
    itoa(i, value, 10);
    std::string name = "HW06Task05_";
    name.append(value);
    name.append(".ppm");
    std::ofstream ppmFileStream(name, std::ios::out | std::ios::binary);
    ppmFileStream << "P3\n"
                  << imageWidth << ' ' << imageHeight << '\n'
                  << maxColorComponent << '\n';
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
    myCamera.truck(0.5);
    myCamera.pan(-2);
  }
}

int main() {
  Task01();
  Task02();
  Task03();
  Task04();
  Task05();
  return 0;
}