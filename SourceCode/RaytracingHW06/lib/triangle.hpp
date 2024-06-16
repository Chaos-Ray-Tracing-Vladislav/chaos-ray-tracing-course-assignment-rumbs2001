#pragma once

#include "vector.hpp"

class Triangle {
 private:
  Vector a, b, c;

 public:
  Triangle(const Vector& inputA, const Vector& inputB, const Vector& inputC)
      : a(inputA), b(inputB), c(inputC) {}

  Vector getNormalVectorForTriangle() const;
  double area() const;

  bool intersect(const Ray& cameraRay) const {
    Vector planeNormal = getNormalVectorForTriangle();
    if (dotProduct(planeNormal, cameraRay.getTo()) != 0 &&
        dotProduct(cameraRay.getTo(), planeNormal) < 0) {
      double coefficient = dotProduct(Vector(cameraRay.getFrom(), a), planeNormal) /
                           dotProduct(cameraRay.getTo(), planeNormal);
      coefficient = coefficient;
      Vector intersection(cameraRay.getTo());
      intersection.scale(coefficient);
      intersection = intersection + cameraRay.getFrom();
      if (dotProduct(planeNormal, crossProduct(Vector(a, b), Vector(a, intersection))) > 0) {
        if (dotProduct(planeNormal, crossProduct(Vector(b, c), Vector(b, intersection))) > 0) {
          if (dotProduct(planeNormal, crossProduct(Vector(c, a), Vector(c, intersection))) > 0) {
            return true;
          }
        }
      }
    }
    return false;
  }

  friend std::ostream& operator<<(std::ostream& os, const Triangle& triangle);
};

Vector Triangle::getNormalVectorForTriangle() const {
  return crossProduct(Vector(a, b), Vector(a, c));
}

double Triangle::area() const {
  return getNormalVectorForTriangle().vectorLength() / 2;
}

std::ostream& operator<<(std::ostream& os, const Triangle& triangle) {
  os << '(' << triangle.a << ',' << triangle.b << ',' << triangle.c << ')';
  return os;
}