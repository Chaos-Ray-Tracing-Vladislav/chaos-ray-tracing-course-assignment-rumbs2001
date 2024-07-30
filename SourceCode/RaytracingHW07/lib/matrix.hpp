#pragma once

#include <cmath>

#include ".\vector.hpp"

const double PI = 3.1415926535;

class Matrix {
 private:
  double values[3][3];

 public:
  Matrix() {
    values[0][0] = 1;
    values[1][0] = 0;
    values[2][0] = 0;
    values[0][1] = 0;
    values[1][1] = 1;
    values[2][1] = 0;
    values[0][2] = 0;
    values[1][2] = 0;
    values[2][2] = 1;
  }

  friend Vector multiplyVectorMatrix(const Vector& vector, const Matrix& matrix) {
    return Vector(
        vector.getX() * matrix.values[0][0] + vector.getY() * matrix.values[1][0] + vector.getZ() * matrix.values[2][0],
        vector.getX() * matrix.values[0][1] + vector.getY() * matrix.values[1][1] + vector.getZ() * matrix.values[2][1],
        vector.getX() * matrix.values[0][2] + vector.getY() * matrix.values[1][2] + vector.getZ() * matrix.values[2][2]);
  }

  friend Matrix multiplyMatrixMatrix(const Matrix& matrix1, const Matrix& matrix2) {
    Matrix result;
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        result.values[i][j] = 0;
      }
    }
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        for (int k = 0; k < 3; ++k) {
          result.values[i][j] += matrix1.values[i][k] * matrix2.values[k][j];
        }
      }
    }
    return result;
  }

  void rotateX(double angle) {
    angle = angle / 180.0 * PI;
    double sinVal = sin(angle);
    double cosVal = cos(angle);
    values[1][1] = cosVal;
    values[2][1] = sinVal;
    values[1][2] = -sinVal;
    values[2][2] = cosVal;
  }

  void rotateY(double angle) {
    angle = angle / 180.0 * PI;
    double sinVal = sin(angle);
    double cosVal = cos(angle);
    values[0][0] = cosVal;
    values[2][0] = -sinVal;
    values[0][2] = sinVal;
    values[2][2] = cosVal;
  }

  void rotateZ(double angle) {
    angle = angle / 180.0 * PI;
    double sinVal = sin(angle);
    double cosVal = cos(angle);
    values[0][0] = cosVal;
    values[1][0] = sinVal;
    values[0][1] = -sinVal;
    values[1][1] = cosVal;
  }

  void setMatrixValues(double input_values[3][3]) {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        values[i][j] = input_values[i][j];
      }
    }
  }
};