#include "uiObject.h"

// Constructor for UIObject
UIObject::UIObject(int width, int height) : width(width), height(height) {}

// Constructor for Button
Button::Button(int width, int height) : UIObject(width, height) {}

Text::Text(int width, int height)
	: UIObject(width, height),
	  size(12),
	  font(nullptr),
	  color{255, 255, 255} { // Default size and color
	alignment.horizontal = Alignment::Horizontal::CENTER;
	alignment.vertical = Alignment::Vertical::MIDDLE;
	alignment.mode = Alignment::PositioningMode::RELATIVE;
}

TextInput::TextInput(int width, int height)
	: UIObject(width, height),
	  textBuffer(""),
	  placeholder(""),
	  isActive(false),
	  textColor{255, 255, 255},
	  backgroundColor{0, 0, 0},
	  maxLength(100),
	  font(nullptr) {
	alignment.horizontal = Alignment::Horizontal::LEFT;
	alignment.vertical = Alignment::Vertical::TOP;
	alignment.mode = Alignment::PositioningMode::RELATIVE;
}
