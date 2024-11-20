#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cmath>
#include <cstddef>
#include <functional>
#include <memory>
#include <stdexcept>
#include <string>

#include "../api/Sprite.h"
#include "../api/Texture.h"
#include "../api/Transform.h"
#include "../util/Log.h"
#include "api/Camera.h"
#include "api/Vector2.h"

#include "SDLContext.h"

using namespace crepe;
using namespace std;

SDLContext & SDLContext::get_instance() {
	static SDLContext instance;
	return instance;
}

SDLContext::SDLContext() {
	dbg_trace();
	// FIXME: read window defaults from config manager

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw std::runtime_error("SDL could not initialize!");
	}
	SDL_Window * tmp_window
		= SDL_CreateWindow("Crepe Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
						   this->viewport.w, this->viewport.h, 0);
	if (!tmp_window) {
		throw std::runtime_error("Window could not be created!");
	}
	this->game_window = {tmp_window, [](SDL_Window * window) { SDL_DestroyWindow(window); }};

	SDL_Renderer * tmp_renderer
		= SDL_CreateRenderer(this->game_window.get(), -1, SDL_RENDERER_ACCELERATED);
	if (!tmp_renderer) {
		throw std::runtime_error("Renderer could not be created!");
	}

	this->game_renderer
		= {tmp_renderer, [](SDL_Renderer * renderer) { SDL_DestroyRenderer(renderer); }};

	int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags)) {
		throw std::runtime_error("SDL_image could not initialize!");
	}
}

SDLContext::~SDLContext() {
	dbg_trace();

	this->game_renderer.reset();
	this->game_window.reset();

	// TODO: how are we going to ensure that these are called from the same
	// thread that SDL_Init() was called on? This has caused problems for me
	// before.
	IMG_Quit();
	SDL_Quit();
}

void SDLContext::handle_events(bool & running) {
	//TODO: wouter i need events
	/*
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			triggerEvent(KeyPressedEvent(getCustomKey(event.key.keysym.sym)));
			break;
		case SDL_MOUSEBUTTONDOWN:
			int x, y;
			SDL_GetMouseState(&x, &y);
			triggerEvent(MousePressedEvent(x, y));
			break;
	}
	*/
}

void SDLContext::clear_screen() { SDL_RenderClear(this->game_renderer.get()); }
void SDLContext::present_screen() { SDL_RenderPresent(this->game_renderer.get()); }


SDL_Rect SDLContext::get_src_rect(const Sprite & sprite) {
	return SDL_Rect{
		.x = sprite.sprite_rect.x,
		.y = sprite.sprite_rect.y,
		.w = sprite.sprite_rect.w,
		.h = sprite.sprite_rect.h,
	};
}
SDL_Rect SDLContext::get_dst_rect(const Sprite & sprite, const Vector2 & pos,
								  const double & scale, const Camera & cam) {

	double adjusted_x = (pos.x - cam.x) * cam.zoom;
	double adjusted_y = (pos.y - cam.y) * cam.zoom;
	double adjusted_w = sprite.sprite_rect.w * scale * cam.zoom;
	double adjusted_h = sprite.sprite_rect.h * scale * cam.zoom;

	return SDL_Rect{
		.x = static_cast<int>(adjusted_x),
		.y = static_cast<int>(adjusted_y),
		.w = static_cast<int>(adjusted_w),
		.h = static_cast<int>(adjusted_h),
	};
}

void SDLContext::draw_particle(const Sprite & sprite, const Vector2 & pos,
							   const double & angle, const double & scale,
							   const Camera & camera) {

	SDL_RendererFlip render_flip
		= (SDL_RendererFlip) ((SDL_FLIP_HORIZONTAL * sprite.flip.flip_x)
						| (SDL_FLIP_VERTICAL * sprite.flip.flip_y));

	SDL_Rect srcrect = this->get_src_rect(sprite);
	SDL_Rect dstrect = this->get_dst_rect(sprite, pos, scale, camera);

	SDL_RenderCopyEx(this->game_renderer.get(), sprite.sprite_image->texture.get(), &srcrect,
				  &dstrect, angle, NULL, render_flip);
}

void SDLContext::draw(const Sprite & sprite, const Transform & transform, const Camera & cam) {

	SDL_RendererFlip render_flip
		= (SDL_RendererFlip) ((SDL_FLIP_HORIZONTAL * sprite.flip.flip_x)
							  | (SDL_FLIP_VERTICAL * sprite.flip.flip_y));

	SDL_Rect srcrect = this->get_src_rect(sprite);
	SDL_Rect dstrect = this->get_dst_rect(sprite, transform.position, transform.scale, cam);

	SDL_RenderCopyEx(this->game_renderer.get(), sprite.sprite_image->texture.get(), &srcrect,
					 &dstrect, transform.rotation, NULL, render_flip);
}

void SDLContext::set_camera(const Camera & cam) {
	this->viewport.w = static_cast<int>(cam.aspect_width);
	this->viewport.h = static_cast<int>(cam.aspect_height);
	this->viewport.x = static_cast<int>(cam.x) - (this->viewport.w / 2);
	this->viewport.y = static_cast<int>(cam.y) - (this->viewport.h / 2);

	SDL_SetRenderDrawColor(this->game_renderer.get(), cam.bg_color.r, cam.bg_color.g,
						   cam.bg_color.b, cam.bg_color.a);
}

uint64_t SDLContext::get_ticks() const { return SDL_GetTicks64(); }

std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>
SDLContext::texture_from_path(const std::string & path) {

	SDL_Surface * tmp = IMG_Load(path.c_str());
	if (tmp == nullptr) {
		tmp = IMG_Load("../asset/texture/ERROR.png");
		if (tmp == nullptr) throw runtime_error("cannot load image");
	}

	std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface *)>> img_surface;
	img_surface = {tmp, [](SDL_Surface * surface) { SDL_FreeSurface(surface); }};

	SDL_Texture * tmp_texture
		= SDL_CreateTextureFromSurface(this->game_renderer.get(), img_surface.get());

	if (tmp_texture == nullptr) {
		throw runtime_error(format("Texture cannot be load from {}", path));
	}

	std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>> img_texture;
	img_texture = {tmp_texture, [](SDL_Texture * texture) { SDL_DestroyTexture(texture); }};

	return img_texture;
}
int SDLContext::get_width(const Texture & ctx) const {
	int w;
	SDL_QueryTexture(ctx.texture.get(), NULL, NULL, &w, NULL);
	return w;
}
int SDLContext::get_height(const Texture & ctx) const {
	int h;
	SDL_QueryTexture(ctx.texture.get(), NULL, NULL, NULL, &h);
	return h;
}
void SDLContext::delay(int ms) const { SDL_Delay(ms); }
