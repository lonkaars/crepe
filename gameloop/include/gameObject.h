#pragma once
#include <iostream>
class GameObject {
	public:
		GameObject();
		GameObject(std::string name, float x, float y, float width, float height, float velX, float velY);
		std::string getName() const;
		float getX() const;
		float getY() const;
		float getWidth() const;
		float getHeight() const;
		float getVelX() const;
		float getVelY() const;
		void setName(std::string value);
		void setX(float value);
		void setY(float value);
		void setWidth(float value);
		void setHeight(float value);
		void setVelX(float value);
		void setVelY(float value);
		int direction;
	private:
		std::string name = "";
		float x = 0;
		float y = 0;
		float width = 0;
		float height = 0;
		float velX = 0;
		float velY = 0;
};
