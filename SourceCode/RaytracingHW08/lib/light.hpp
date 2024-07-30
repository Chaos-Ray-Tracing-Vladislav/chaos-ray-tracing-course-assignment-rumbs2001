#pragma once

#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "vector.hpp"

struct Light {
  int intensity;
  Vector position;
};
