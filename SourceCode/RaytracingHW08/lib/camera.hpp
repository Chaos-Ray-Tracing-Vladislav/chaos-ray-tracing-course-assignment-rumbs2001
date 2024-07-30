#pragma once

#include ".\imgprop.hpp"
#include ".\matrix.hpp"
#include ".\ray.hpp"
#include ".\vector.hpp"

class Camera {
 private:
  Vector position;
  Vector lookAt;
  Matrix changeMatrix;

 public:
  Camera()
      : position(Vector(0, 0, 0)), lookAt(Vector(0, 0, -1)) {}

  Ray getProjectedVector(int screenX, int screenY, int imageWidth, int imageHeight) const {
    Vector to(lookAt);
    double x = (2.0 * ((screenX + 0.5) / imageWidth) - 1.0) * (imageWidth / imageHeight);
    double y = 1.0 - 2.0 * ((screenY + 0.5) / imageHeight);
    to.setX(x);
    to.setY(y);
    to.setZ(-1.0);
    to = multiplyVectorMatrix(to, changeMatrix);
    to.normalize();
    return Ray(position, to);
  }

  void dolly(double value) {
    position.setZ(position.getZ() + value);
  }

  void truck(double value) {
    position.setX(position.getX() + value);
  }

  void pedestal(double value) {
    position.setY(position.getY() + value);
  }

  void pan(double value) {
    Matrix rotation;
    rotation.rotateY(value);
    changeMatrix = multiplyMatrixMatrix(changeMatrix, rotation);
  }

  void tilt(double value) {
    Matrix rotation;
    rotation.rotateX(value);
    changeMatrix = multiplyMatrixMatrix(changeMatrix, rotation);
  }

  void roll(double value) {
    Matrix rotation;
    rotation.rotateZ(value);
    changeMatrix = multiplyMatrixMatrix(changeMatrix, rotation);
  }

  void setPosition(const Vector& input_position) {
    position = input_position;
  }

  void applyMatrix(Matrix input_matrix) {
    changeMatrix = multiplyMatrixMatrix(changeMatrix, input_matrix);
  }
};