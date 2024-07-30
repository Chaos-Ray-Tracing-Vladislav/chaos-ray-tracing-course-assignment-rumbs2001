#pragma once

#include <cmath>

class Vector {
 private:
  double x, y, z;

 public:
  Vector()
      : x(0.0f), y(0.0f), z(0.0f) {}

  Vector(double inputX, double inputY, double inputZ)
      : x(inputX), y(inputY), z(inputZ) {}

  Vector(const Vector& a, const Vector& b)
      : x(b.x - a.x), y(b.y - a.y), z(b.z - a.z) {}

  Vector& operator=(const Vector& other);

  /// Setters ----------------------------------------------------------

  void setX(double value);
  void setY(double value);
  void setZ(double value);
  void scale(double factor);

  /// Getters ----------------------------------------------------------

  double getX() const;
  double getY() const;
  double getZ() const;
  double vectorLength(void) const;

  /// Methods of the object --------------------------------------------

  void normalize();

  /// Friend methods ---------------------------------------------------

  friend Vector operator+(const Vector& a, const Vector& b);
  friend Vector operator*(const Vector& a, const float coef);
  friend Vector crossProduct(const Vector& a, const Vector& b);
  friend double dotProduct(const Vector& a, const Vector& b);
  friend std::ostream& operator<<(std::ostream& os, const Vector& vector);
};

Vector& Vector::operator=(const Vector& other) {
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
  return *this;
}

/// Setters ------------------------------------------------------------

void Vector::setX(double value) {
  this->x = value;
}

void Vector::setY(double value) {
  this->y = value;
}

void Vector::setZ(double value) {
  this->z = value;
}

void Vector::scale(double factor) {
  x *= factor;
  y *= factor;
  z *= factor;
}

/// Getters ------------------------------------------------------------

double Vector::getX() const {
  return this->x;
}

double Vector::getY() const {
  return this->y;
}

double Vector::getZ() const {
  return this->z;
}

/// Methods of the object ----------------------------------------------

double Vector::vectorLength(void) const {
  return sqrt(x * x + y * y + z * z);
}

void Vector::normalize() {
  double length = 1.0 / this->vectorLength();
  x *= length;
  y *= length;
  z *= length;
}

/// Friend operators ---------------------------------------------------

Vector operator+(const Vector& a, const Vector& b) {
  return Vector(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector operator*(const Vector& a, const float coef) {
  return Vector(a.x * coef, a.y * coef, a.z + coef);
}

Vector crossProduct(const Vector& a, const Vector& b) {
  return Vector(a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x);
}

double dotProduct(const Vector& a, const Vector& b) {
  return (a.x * b.x + a.y * b.y + a.z * b.z);
}

std::ostream& operator<<(std::ostream& os, const Vector& vector) {
  os << '(' << vector.x << ',' << vector.y << ',' << vector.z << ')';
  return os;
}