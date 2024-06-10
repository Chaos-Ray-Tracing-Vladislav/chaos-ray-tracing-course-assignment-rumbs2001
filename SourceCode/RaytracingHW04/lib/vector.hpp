#pragma once

#include <cmath>

class Vector {
 private:
  double x, y, z;

 public:
  Vector(double inputX, double inputY, double inputZ)
      : x(inputX), y(inputY), z(inputZ) {}

  Vector(const Vector& a, const Vector& b)
      : x(b.x - a.x), y(b.y - a.y), z(b.z - a.z) {}

  double vectorLength(void) const;

  friend Vector crossProduct(const Vector& a, const Vector& b);
  friend std::ostream& operator<<(std::ostream& os, const Vector& vector);
};

double Vector::vectorLength(void) const {
  return sqrt(x * x + y * y + z * z);
}

Vector crossProduct(const Vector& a, const Vector& b) {
  return Vector(a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x);
}

std::ostream& operator<<(std::ostream& os, const Vector& vector) {
  os << '(' << vector.x << ',' << vector.y << ',' << vector.z << ')';
  return os;
}