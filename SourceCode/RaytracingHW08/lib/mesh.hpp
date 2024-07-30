#pragma once

#include <vector>

#include "./triangle.hpp"
#include "./vector.hpp"

class Mesh : public SceneObject {
 private:
  struct MeshTriangle {
    int vertices[3];
  };

  std::vector<Vector> meshVertices;
  std::vector<MeshTriangle> meshTriangles;

 public:
  void addVertex(const Vector& vertex) {
    meshVertices.push_back(vertex);
  }

  void addTriangle(const int vertex1, const int vertex2, const int vertex3) {
    meshTriangles.push_back(MeshTriangle{vertex1, vertex2, vertex3});
  }

  bool intersect(const Ray& cameraRay, IntersectionData& intersectionData) const override {
    bool isIntersected = false;
    Triangle triangle;
    IntersectionData intersectionDataTemp;
    for (const MeshTriangle& meshTriangle : meshTriangles) {
      triangle.a = meshVertices[meshTriangle.vertices[0]];
      triangle.b = meshVertices[meshTriangle.vertices[1]];
      triangle.c = meshVertices[meshTriangle.vertices[2]];
      if (triangle.intersect(cameraRay, intersectionDataTemp)) {
        isIntersected = true;
        intersectionData = intersectionDataTemp;
        // if (intersectionData.distance == 0 || intersectionDataTemp.distance < intersectionData.distance) {
        // }
      }
    }
    return isIntersected;
  }
};
