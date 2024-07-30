#pragma once

class Color {
 private:
  float red, green, blue;

 public:
  Color() : red(0.0f), green(0.0f), blue(0.0f) {}

  Color(float input_red, float input_green, float input_blue)
      : red(input_red), green(input_green), blue(input_blue) {}

  float getRed() { return red; }
  float getGreen() { return green; }
  float getBlue() { return blue; }

  void setRed(float input_red) { red = input_red; }
  void setGreen(float input_green) { green = input_green; }
  void setBlue(float input_blue) { blue = input_blue; }

  static int colorFloatToInt(float value) {
    return (int)(value * 255);
  }

  friend std::ostream& operator<<(std::ostream& os, const Color& color);
  friend Color operator*(const Color& a, const float coef);

  void operator+=(const Color& other) {
    red += other.red;
    green += other.green;
    blue += other.blue;
  }
};

std::ostream& operator<<(std::ostream& os, const Color& color) {
  os << Color::colorFloatToInt(color.red) << ' '
     << Color::colorFloatToInt(color.green) << ' '
     << Color::colorFloatToInt(color.blue);
  return os;
}

Color operator*(const Color& a, const float coef) {
  return Color(a.red * coef, a.green * coef, a.blue * coef);
}