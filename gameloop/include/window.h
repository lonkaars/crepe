#pragma once
#include <SDL2/SDL.h>
class WindowManager{
	public:
		WindowManager();
		virtual ~WindowManager();
		bool loadMedia();
		void update();
		bool init();
		void close();
		bool initWindow();
		void destroyWindow();
		SDL_Renderer* getRenderer();
	private:
		//Loads media
		//Frees media and shuts down SDL
		
		const int SCREEN_WIDTH = 800;
		const int SCREEN_HEIGHT = 600;
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;
};
