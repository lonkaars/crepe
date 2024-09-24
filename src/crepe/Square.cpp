#include "Square.hpp"
#include <iostream> 

Square::Square(float xPos, float yPos, int w, int h)
    : x(xPos), y(yPos), width(w), height(h) {}

void Square::Draw() {
  
    std::cout << "Drawing square at (" << x << ", " << y << ") with dimensions " << width << "x" << height << std::endl;
}
