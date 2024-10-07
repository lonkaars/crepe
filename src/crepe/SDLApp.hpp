#ifndef SDLAPP_HPP
#define SDLAPP_HPP

#include <SDL2/SDL.h>

class SDLApp {
public:
    SDLApp(int windowWidth, int windowHeight);
    ~SDLApp();

    bool initialize();
    void handleEvents(bool& running);
    void clearScreen();
    void presentScreen();
    void drawSquare(int x, int y, int size);
    void cleanUp();

private:
    int windowWidth;
    int windowHeight;
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif
