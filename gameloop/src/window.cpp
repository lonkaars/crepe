#include "window.h"

WindowManager::WindowManager(){
	if( !initWindow() )
	{
		printf( "Failed to initialize!\n" );
	}
}
WindowManager::~WindowManager(){
	destroyWindow();
}
bool WindowManager::init()
{
}
bool WindowManager::loadMedia()
{
}
void WindowManager::close()
{

}
SDL_Renderer* WindowManager::getRenderer(){
	return renderer;
}
void WindowManager::update(){
}
bool WindowManager::initWindow(){
	if(SDL_Init(SDL_INIT_EVERYTHING) !=  0){
		fprintf(stderr,"Error inititalising SDL.\n");
		return false;
	} 
	window = SDL_CreateWindow("Gameloop POC",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_RESIZABLE);
	if(!window){
		fprintf(stderr,"Error creating SDL Window. \n");
		return false;
	}
	renderer = SDL_CreateRenderer(window,-1,0);
	if(!renderer){
		fprintf(stderr,"Error creating SDL renderer. \n");
		return false;
	}
	return true;
}
void WindowManager::destroyWindow(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
