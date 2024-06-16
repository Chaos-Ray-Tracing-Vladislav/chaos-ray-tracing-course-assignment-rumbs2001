#pragma once

#include ".\ray.hpp"
#include ".\vector.hpp"

/// Output image resolution

static const int imageWidth = 800;
static const int imageHeight = 600;
static const int maxColorComponent = 255;

class Camera {
 private:
  Vector position;
  Vector lookAt;

 public:
  Camera(const Vector& inputPosition, const Vector& inputLookAt)
      : position(inputPosition), lookAt(inputLookAt) {}

  Ray getProjectedVector(int screenX, int screenY) {
    Vector to(lookAt);
    double x = (2.0 * ((screenX + 0.5) / imageWidth) - 1.0) * (imageWidth / imageHeight);
    double y = 1.0 - 2.0 * ((screenY + 0.5) / imageHeight);
    to.setX(x);
    to.setY(y);
    to.setZ(-1.0);
    to.normalize();
    return Ray(position, to);
  }
};