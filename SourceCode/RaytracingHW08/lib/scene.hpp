#pragma once

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "./rapidjson/document.h"
#include "./rapidjson/istreamwrapper.h"
#include "./rapidjson/stringbuffer.h"
#include "./rapidjson/writer.h"
#include "camera.hpp"
#include "light.hpp"
#include "mesh.hpp"
#include "settings.hpp"

class Scene {
 private:
  std::vector<Mesh> geometryObjects;
  std::vector<Light> lights;
  Camera camera;
  Settings settings;

 public:
  Scene(const std::string& sceneFileName) {
    parseSceneFile(sceneFileName);
  }

  const std::vector<Mesh>& getGeometryObjects() const {
    return geometryObjects;
  }

  const std::vector<Light>& getLights() const {
    return lights;
  }

  const Camera& getCamera() const {
    return camera;
  }
  const Settings& getSettings() const {
    return settings;
  }

  void parseSceneFile(const std::string& sceneFileName);
};

rapidjson::Document getJsonDocument(const std::string& filename) {
  std::ifstream ifs(filename);
  assert(ifs.is_open());
  rapidjson::IStreamWrapper isw(ifs);
  rapidjson::Document doc;
  doc.ParseStream(isw);
  if (doc.HasParseError()) {
    std::cout << "Error: " << doc.GetParseError() << '\n';
    std::cout << "Offset: " << doc.GetErrorOffset() << '\n';
    assert(false);
  }
  assert(doc.IsObject());
  return doc;
}

void Scene::parseSceneFile(const std::string& sceneFileName) {
  rapidjson::Document doc = getJsonDocument(sceneFileName);

  const rapidjson::Value& settingsVal = doc.FindMember("settings")->value;
  if (!settingsVal.IsNull() && settingsVal.IsObject()) {
    const rapidjson::Value& bgColorVal = settingsVal.FindMember("background_color")->value;
    assert(!bgColorVal.IsNull() && bgColorVal.IsArray());
    settings.backgroundColor.setRed(bgColorVal.GetArray()[0].GetFloat());
    settings.backgroundColor.setGreen(bgColorVal.GetArray()[1].GetFloat());
    settings.backgroundColor.setBlue(bgColorVal.GetArray()[2].GetFloat());

    const rapidjson::Value& imageSettingsVal = settingsVal.FindMember("image_settings")->value;
    if (!imageSettingsVal.IsNull() && imageSettingsVal.IsObject()) {
      const rapidjson::Value& imageWidthVal = imageSettingsVal.FindMember("width")->value;
      const rapidjson::Value& imageHeightVal = imageSettingsVal.FindMember("height")->value;
      assert(!imageWidthVal.IsNull() && imageWidthVal.IsInt());
      assert(!imageHeightVal.IsNull() && imageHeightVal.IsInt());
      settings.imageWidth = imageWidthVal.GetInt();
      settings.imageHeight = imageHeightVal.GetInt();
    }
  }

  const rapidjson::Value& cameraVal = doc.FindMember("camera")->value;
  if (!cameraVal.IsNull() && cameraVal.IsObject()) {
    const rapidjson::Value& matrixVal = cameraVal.FindMember("matrix")->value;
    assert(!matrixVal.IsNull() && matrixVal.IsArray());
    Matrix jsonMatrix;
    double input_values[3][3];
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        input_values[i][j] = matrixVal.GetArray()[i * 3 + j].GetFloat();
      }
    }
    jsonMatrix.setMatrixValues(input_values);
    camera.applyMatrix(jsonMatrix);
    const rapidjson::Value& positionVal = cameraVal.FindMember("position")->value;
    assert(!positionVal.IsNull() && positionVal.IsArray());
    camera.setPosition(Vector{positionVal.GetArray()[0].GetFloat(),
                              positionVal.GetArray()[1].GetFloat(),
                              positionVal.GetArray()[2].GetFloat()});
  }

  const rapidjson::Value& objectsVal = doc.FindMember("objects")->value;
  if (!objectsVal.IsNull() && objectsVal.IsArray()) {
    for (int i = 0; i < objectsVal.GetArray().Size(); ++i) {
      Mesh newMesh;

      const rapidjson::Value& verticesVal = objectsVal.GetArray()[i].FindMember("vertices")->value;
      assert(!verticesVal.IsNull() && verticesVal.IsArray());
      for (int j = 0; j < verticesVal.GetArray().Size(); j += 3) {
        newMesh.addVertex(Vector{verticesVal.GetArray()[j].GetFloat(),
                                 verticesVal.GetArray()[j + 1].GetFloat(),
                                 verticesVal.GetArray()[j + 2].GetFloat()});
      }

      const rapidjson::Value& trianglesVal = objectsVal.GetArray()[i].FindMember("triangles")->value;
      assert(!trianglesVal.IsNull() && trianglesVal.IsArray());
      for (int j = 0; j < trianglesVal.GetArray().Size(); j += 3) {
        newMesh.addTriangle(trianglesVal.GetArray()[j].GetInt(),
                            trianglesVal.GetArray()[j + 1].GetInt(),
                            trianglesVal.GetArray()[j + 2].GetInt());
      }

      geometryObjects.push_back(newMesh);
    }
  }

  const rapidjson::Value& lightsVal = doc.FindMember("lights")->value;
  if (!lightsVal.IsNull() && lightsVal.IsArray()) {
    for (int i = 0; i < lightsVal.GetArray().Size(); ++i) {
      Light newLight;

      const rapidjson::Value& intensityVal = lightsVal.GetArray()[i].FindMember("intensity")->value;
      assert(!intensityVal.IsNull() && intensityVal.IsInt());
      newLight.intensity = intensityVal.GetInt();

      const rapidjson::Value& positionVal = lightsVal.GetArray()[i].FindMember("position")->value;
      assert(!positionVal.IsNull() && positionVal.IsArray());
      newLight.position = Vector(positionVal.GetArray()[0].GetFloat(),
                                 positionVal.GetArray()[1].GetFloat(),
                                 positionVal.GetArray()[2].GetFloat());

      lights.push_back(newLight);
    }
  }
}