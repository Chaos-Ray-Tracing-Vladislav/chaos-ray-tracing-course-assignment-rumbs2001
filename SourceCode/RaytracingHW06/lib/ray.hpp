#pragma once

#include ".\vector.hpp"

class Ray {
 private:
  Vector from;
  Vector to;

 public:
  Ray(const Vector& inputFrom, const Vector& inputTo)
      : from(inputFrom), to(inputTo) {}

  void setFrom(const Vector& inputFrom) {
    from = inputFrom;
  }

  void setTo(const Vector& inputTo) {
    to = inputTo;
  }

  const Vector& getFrom() const {
    return from;
  }

  const Vector& getTo() const {
    return to;
  }
};