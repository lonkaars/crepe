#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "uiObject.h"

class UIRenderer {
public:
    UIRenderer(SDL_Renderer* renderer);
    void render(UIObject* uiObject);

private:
    SDL_Renderer* renderer;

    void renderButton(Button* button);
    void renderText(Text* text);
    void renderTextInput(TextInput* textInput);
};
