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