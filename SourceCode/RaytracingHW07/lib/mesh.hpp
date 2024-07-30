#pragma once

#include <vector>

#include "./triangle.hpp"
#include "./vector.hpp"

class Mesh {
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

  bool isIntersected(const Ray& cameraRay) const {
    bool isIntersected = false;
    for (const MeshTriangle& meshTriangle : meshTriangles) {
      Triangle triangle(meshVertices[meshTriangle.vertices[0]],
                        meshVertices[meshTriangle.vertices[1]],
                        meshVertices[meshTriangle.vertices[2]]);
      if (triangle.intersect(cameraRay)) {
        isIntersected = true;
        break;
      }
    }
    return isIntersected;
  }
};
