#pragma once
#include "gameObject.h"
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include "event.h"
#include "eventHandler.h"
#include <functional>
struct Alignment {
    enum class Horizontal { LEFT, CENTER, RIGHT };
    enum class Vertical { TOP, MIDDLE, BOTTOM };
    enum class PositioningMode { RELATIVE, STATIC,ABSOLUTE };

    Horizontal horizontal = Horizontal::CENTER;
    Vertical vertical = Vertical::MIDDLE;
    PositioningMode mode = PositioningMode::RELATIVE;

    int staticX = 0;
    int staticY = 0;

    int marginTop = 0;
    int marginBottom = 0;
    int marginLeft = 0;
    int marginRight = 0;
};
struct RGBColor{
	int red;
	int green;
	int blue;
};
class UIObject : public GameObject{
	public:
	UIObject(int width,int height);
	virtual ~UIObject() {}
	int width;
	int height;
	int x;
	int y;
};
class Button : public UIObject{
	public:
	Button(int width,int height);
	RGBColor color;
	std::function<void()> onClick;

};
class Text : public UIObject{
	public:
	Text(int width,int height);
	std::string text;
	int size;
	Alignment alignment;
	//font resource
	TTF_Font *font;
	RGBColor color;
};
class TextInput : public UIObject {
public:
    TextInput(int width, int height);
    std::string textBuffer;          
    std::string placeholder;
    bool isActive = false;
    RGBColor textColor;
    RGBColor backgroundColor;
    size_t maxLength = 100;
    Alignment alignment;
    TTF_Font* font = nullptr;
    std::function<void()> onSubmit; 
	std::function<void()> onFocus; 
};

