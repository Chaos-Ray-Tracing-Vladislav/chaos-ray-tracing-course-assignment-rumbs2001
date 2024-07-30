#pragma once

#include "vector.hpp"

struct IntersectionData {
  Vector position;
  Vector normal;
  double distance;
};

class SceneObject {
 public:
  virtual bool intersect(const Ray& cameraRay, IntersectionData& intersectionData) const = 0;
};

class Triangle : public SceneObject {
 private:
 public:
  Vector a, b, c;
  Triangle() {}
  Triangle(const Vector& inputA, const Vector& inputB, const Vector& inputC)
      : a(inputA), b(inputB), c(inputC) {}

  Vector getNormalVectorForTriangle() const;
  double area() const;

  bool intersect(const Ray& cameraRay, IntersectionData& intersectionData) const override {
    Vector planeNormal = getNormalVectorForTriangle();
    if (dotProduct(planeNormal, cameraRay.getTo()) != 0 &&
        dotProduct(cameraRay.getTo(), planeNormal) < 0) {
      double coefficient = dotProduct(Vector(cameraRay.getFrom(), a), planeNormal) /
                           dotProduct(cameraRay.getTo(), planeNormal);
      Vector intersection(cameraRay.getTo());
      intersection.scale(coefficient);
      intersection = intersection + cameraRay.getFrom();
      if (dotProduct(planeNormal, crossProduct(Vector(a, b), Vector(a, intersection))) > 0) {
        if (dotProduct(planeNormal, crossProduct(Vector(b, c), Vector(b, intersection))) > 0) {
          if (dotProduct(planeNormal, crossProduct(Vector(c, a), Vector(c, intersection))) > 0) {
            intersectionData.position = intersection;
            planeNormal.normalize();
            intersectionData.normal = planeNormal;
            Vector distanceVector(cameraRay.getFrom(), intersection);
            intersectionData.distance = distanceVector.vectorLength();
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