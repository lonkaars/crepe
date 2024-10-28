#include "gameObject.h"
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include "event.h"
#include "eventHandler.h"
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
	int red,
	int green,
	int blue
};
class UIObject : public GameObject{
	public:
	UIObject(int width,int height);
	private:
	int width;
	int height;
};
class Button : public UIObject{
	public:
	Button(int width,int height);
	EventHandler<KeyPressedEvent> onKeyPressed;
	EventHandler<KeyReleasedEvent> onKeyReleased;

};
class Text : public UIObject{
	public:
	Text(int width,int height);
	private:
	std::string text;
	int size;
	Alignment alignment;
	//font resource
	TTF_Font *font;
	RGBColor color;
};
class TextInput : public UIObject{
	public:
	TextInput (int width,int height);
	std::string textBuffer;
    std::string placeholder;
    size_t caretPosition;
    bool isActive;
    RGBColor textColor;
    RGBColor backgroundColor;
    size_t maxLength;
    Alignment alignment;
    TTF_Font* font;
	EventHandler<TextSubmitEvent> onSubmit;
};
