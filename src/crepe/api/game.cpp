


#include "game.h"
#include "core/renderSystem.h"
#include "facade/SdlContext.h"


Engine::Engine(int windowHeight, int window_with){
	crepe::SdlContext& ctx = crepe::SdlContext::get_instance();
}



void Engine::loop() {

	bool running = true;
	crepe::SdlContext& ctx = crepe::SdlContext::get_instance();
	RenderSystem rendering;

	while (running) {
		ctx.handleEvents(running);

		ctx.clearScreen();

		rendering.render();

		ctx.presentScreen();
	}
}
