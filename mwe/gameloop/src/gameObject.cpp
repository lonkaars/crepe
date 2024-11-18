#include "gameObject.h"
std::string GameObject::getName() const { return name; }
float GameObject::getX() const { return x; }

float GameObject::getY() const { return y; }

float GameObject::getWidth() const { return width; }

float GameObject::getHeight() const { return height; }

float GameObject::getVelX() const { return velX; }

float GameObject::getVelY() const { return velY; }
void GameObject::setName(std::string value) { name = value; }
void GameObject::setX(float value) { x = value; }

void GameObject::setY(float value) { y = value; }

void GameObject::setWidth(float value) { width = value; }

void GameObject::setHeight(float value) { height = value; }

void GameObject::setVelX(float value) { velX = value; }

void GameObject::setVelY(float value) { velY = value; }

GameObject::GameObject(std::string name, float x, float y, float width, float height,
					   float velX, float velY)
	: name(name),
	  x(x),
	  y(y),
	  width(width),
	  height(height),
	  velX(velX),
	  velY(velY) {}
