#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include "uiObject.h"

class UIRenderer {
public:
    UIRenderer(SDL_Renderer* renderer);
    ~UIRenderer();

    void render(UIObject* uiObject);

private:
    SDL_Renderer* renderer;
    TTF_Font* font;

    void renderButton(Button* button);
    void renderText(Text* text);
    void renderTextInput(TextInput* textInput);
};
