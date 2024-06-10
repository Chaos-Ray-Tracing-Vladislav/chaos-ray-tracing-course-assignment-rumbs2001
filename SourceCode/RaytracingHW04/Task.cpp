#include <iostream>

#include "./lib/triangle.hpp"
#include "./lib/vector.hpp"

void Task01() {
  // Task 01
  std::cout << "Task 01\n";
  Triangle triangle(Vector(1, 0, 0), Vector(0, 1, 0), Vector(0, 0, 1));
  std::cout << triangle << std::endl;
}

void Task02() {
  // Task 02
  std::cout << "Task 02\n";
  {
    Vector A(3.5, 0, 0), B(1.75, 3.5, 0);
    std::cout << crossProduct(A, B) << std::endl;
  }
  {
    Vector A(3, -3, 1), B(4, 9, 3);
    std::cout << crossProduct(A, B) << std::endl;
  }
  {
    Vector A(3, -3, 1), B(4, 9, 3);
    std::cout << crossProduct(A, B).vectorLength() << std::endl;
  }
  {
    Vector A(3, -3, 1), B(-12, 12, -4);
    std::cout << crossProduct(A, B).vectorLength() << std::endl;
  }
}

void Task03() {
  // Task 03
  std::cout << "Task 03\n";
  {
    Triangle triangle(Vector(-1.75, -1.75, -3), Vector(1.75, -1.75, -3), Vector(0, 1.75, -3));
    std::cout << triangle.getNormalVectorForTriangle() << std::endl;
    std::cout << triangle.area() << std::endl;
  }
  {
    Triangle triangle(Vector(0, 0, -1), Vector(1, 0, 1), Vector(-1, 0, 1));
    std::cout << triangle.getNormalVectorForTriangle() << std::endl;
    std::cout << triangle.area() << std::endl;
  }
  {
    Triangle triangle(Vector(0.56, 1.11, 1.23), Vector(0.44, -2.368, -0.54), Vector(-1.56, 0.15, -1.92));
    std::cout << triangle.getNormalVectorForTriangle() << std::endl;
    std::cout << triangle.area() << std::endl;
  }
}

int main() {
  Task01();
  Task02();
  Task03();
  return 0;
}