#pragma once

#include "color.hpp"

struct Settings {
 public:
  Color backgroundColor;
  int imageWidth;
  int imageHeight;

  //  public:
  //   Settings(const Color& input_backgroundColor,
  //            const int input_imageWidth,
  //            const int input_imageHeight)
  //       : backgroundColor(input_backgroundColor),
  //         imageWidth(input_imageWidth),
  //         imageHeight(input_imageHeight) {}

  //   Color getBackgroundColor() { return backgroundColor; }
  //   int getImageWidth() { return imageWidth; }
  //   int getImageHeight() { return imageHeight; }

  //   void setBackgroundColor(const Color& input_backgroundColor) { backgroundColor = input_backgroundColor; }
  //   void setImageWidth(const int input_imageWidth) { imageWidth = input_imageWidth; }
  //   void setImageHeight(const int input_imageHeight) { imageHeight = input_imageHeight; }
};