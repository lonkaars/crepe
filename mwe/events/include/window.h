#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include "uiObject.h"
#include "uiRenderer.h"

class WindowManager {
public:
    WindowManager();
    virtual ~WindowManager();

    bool initWindow();
    void destroyWindow();
    SDL_Renderer* getRenderer();

    void addUIObject(UIObject* uiObject);
    void renderUIObjects();

private:
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    UIRenderer* uiRenderer;
    std::vector<UIObject*> uiObjects;
};
