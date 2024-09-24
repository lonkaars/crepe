#pragma once

#include <SDL.h>
#include <string>

class ViewFacade {
public:
    ViewFacade();
    ~ViewFacade();

    bool initialize(const std::string& title, int width, int height);
    void clear();
    void present();
    void handleEvents();
    bool isRunning() const;
    void drawSquare(int x, int y, int w, int h, int r, int g, int b);
    void updateDeltaTime();
    float getDeltaTime() const;
    bool isSpacePressed() const;

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    Uint32 lastFrameTime;
    float deltaTime;
};
