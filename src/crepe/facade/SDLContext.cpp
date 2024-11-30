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
#include <iostream>
#include <memory>
#include <stdexcept>

#include "../api/Camera.h"
#include "../api/Config.h"
#include "../api/Sprite.h"
#include "../api/Texture.h"
#include "../util/Log.h"

#include "SDLContext.h"
#include "types.h"

using namespace crepe;
using namespace std;

SDLContext & SDLContext::get_instance() {
	static SDLContext instance;
	return instance;
}

SDLContext::SDLContext() {
	dbg_trace();

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw runtime_error(format("SDLContext: SDL_Init error: {}", SDL_GetError()));
	}

	auto & cfg = Config::get_instance().window_settings;
	SDL_Window * tmp_window
		= SDL_CreateWindow(cfg.window_title.c_str(), SDL_WINDOWPOS_CENTERED,
						   SDL_WINDOWPOS_CENTERED, cfg.default_size.x, cfg.default_size.y, 0);
	if (!tmp_window) {
		throw runtime_error(format("SDLContext: SDL_Window error: {}", SDL_GetError()));
	}
	this->game_window = {tmp_window, [](SDL_Window * window) { SDL_DestroyWindow(window); }};

	SDL_Renderer * tmp_renderer
		= SDL_CreateRenderer(this->game_window.get(), -1, SDL_RENDERER_ACCELERATED);
	if (!tmp_renderer) {
		throw runtime_error(
			format("SDLContext: SDL_CreateRenderer error: {}", SDL_GetError()));
	}

	this->game_renderer
		= {tmp_renderer, [](SDL_Renderer * renderer) { SDL_DestroyRenderer(renderer); }};

	int img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(img_flags) & img_flags)) {
		throw runtime_error("SDLContext: SDL_image could not initialize!");
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

void SDLContext::clear_screen() {
	SDL_SetRenderDrawColor(this->game_renderer.get(), 255, 255, 255, 255);
	SDL_RenderClear(this->game_renderer.get());
}
void SDLContext::present_screen() { SDL_RenderPresent(this->game_renderer.get()); }

SDL_Rect SDLContext::get_src_rect(const Sprite & sprite) const {
	return SDL_Rect{
		.x = sprite.mask.x,
		.y = sprite.mask.y,
		.w = sprite.mask.w,
		.h = sprite.mask.h,
	};
}

vec2 bar_size;
vec2 scale;

SDL_FRect SDLContext::get_dst_rect(const Sprite & sprite, const vec2 & pos, const Camera & cam,
								  const vec2 & cam_pos, const double & img_scale) const {


	vec2 size = { (sprite.height * sprite.aspect_ratio), sprite.height};
	
	size *=  scale * img_scale * cam.zoom ;

	vec2 screen_pos = (pos - cam_pos + cam.viewport_size / 2) * scale - size / 2 + bar_size;

	cout << size.x << " " << size.y << endl;
	cout << pos.x << " " << pos.y << endl;
	cout << scale.x << " " << scale.y << endl;
	cout << screen_pos.x << " " << screen_pos.y << endl;

	return SDL_FRect{
		.x = screen_pos.x,
		.y = screen_pos.y,
		.w = size.x,
		.h = size.y,
	};
}

void SDLContext::draw(const RenderContext & ctx) {

	SDL_RendererFlip render_flip
		= (SDL_RendererFlip) ((SDL_FLIP_HORIZONTAL * ctx.sprite.flip.flip_x)
							  | (SDL_FLIP_VERTICAL * ctx.sprite.flip.flip_y));

	SDL_Rect srcrect = this->get_src_rect(ctx.sprite);
	SDL_FRect dstrect
		= this->get_dst_rect(ctx.sprite, ctx.pos, ctx.cam, ctx.cam_pos, ctx.scale);

	cout << dstrect.x << " " << dstrect.y << " " << dstrect.w << " " << dstrect.h << endl;

	SDL_RenderCopyExF(this->game_renderer.get(), ctx.sprite.sprite_image.texture.get(),
					 &srcrect, &dstrect, ctx.angle, NULL, render_flip);
}

void SDLContext::set_camera(const Camera & cam) {

	// resize window
	int w, h;
	SDL_GetWindowSize(this->game_window.get(), &w, &h);
	if (w != cam.screen.x || h != cam.screen.y) {
		SDL_SetWindowSize(this->game_window.get(), cam.screen.x, cam.screen.y);
	}

	double screen_aspect = static_cast<double>(cam.screen.x) / cam.screen.y;
	double viewport_aspect = cam.viewport_size.x / cam.viewport_size.y;


	SDL_FRect black_bars[2];
	// calculate black bars
	if (screen_aspect > viewport_aspect) {
		// pillarboxing
		cout << "pillarboxing" << endl;
		float render_scale = cam.screen.y / cam.viewport_size.y;
		float adj_width = cam.viewport_size.x * render_scale;
		float bar_width = (cam.screen.x - adj_width) / 2;
		black_bars[0] = {0, 0, bar_width, (float) cam.screen.y};
		black_bars[1] = {(cam.screen.x - bar_width), 0, bar_width, (float) cam.screen.y};

		bar_size = {bar_width,0};
		scale.x = scale.y = cam.screen.y / cam.viewport_size.y;
	} else {
		// letterboxing
		cout << "letterboxing" << endl;
		float render_scale = cam.screen.x / cam.viewport_size.x;
		float adj_height = cam.viewport_size.y * render_scale;
		float bar_height = (cam.screen.y - adj_height) / 2;
		black_bars[0] = {0, 0, (float) cam.screen.x, bar_height};
		black_bars[1] = {0, (cam.screen.y - bar_height), (float) cam.screen.x, bar_height};

		bar_size = {0,bar_height};
		scale.x = scale.y = render_scale;
	}

	cout << "BARS" << endl;

	for (int i = 0; i < 2; ++i) {
		cout << black_bars[i].x << " " << black_bars[i].y << " " << black_bars[i].w << " "
			 << black_bars[i].h << endl;
	}

	SDL_SetRenderDrawColor(this->game_renderer.get(), 0, 0, 0, 255);
	SDL_RenderFillRectF(this->game_renderer.get(), &black_bars[0]);
	SDL_RenderFillRectF(this->game_renderer.get(), &black_bars[1]);

	/*
	// set bg color
	SDL_SetRenderDrawColor(this->game_renderer.get(), cam.bg_color.r, cam.bg_color.g,
						   cam.bg_color.b, cam.bg_color.a);

	SDL_Rect bg = {
		.x = 0,
		.y = 0,
		.w = (int)cam.viewport_size.x,
		.h = (int)cam.viewport_size.y,
	};
	// fill bg color
	SDL_RenderFillRect(this->game_renderer.get(), &bg);

	*/
}

uint64_t SDLContext::get_ticks() const { return SDL_GetTicks64(); }

std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture *)>>
SDLContext::texture_from_path(const std::string & path) {

	SDL_Surface * tmp = IMG_Load(path.c_str());
	if (tmp == nullptr)
		throw runtime_error(format("SDLContext: IMG_Load error: {}", SDL_GetError()));

	std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface *)>> img_surface;
	img_surface = {tmp, [](SDL_Surface * surface) { SDL_FreeSurface(surface); }};

	SDL_Texture * tmp_texture
		= SDL_CreateTextureFromSurface(this->game_renderer.get(), img_surface.get());

	if (tmp_texture == nullptr) {
		throw runtime_error(format("SDLContext: Texture cannot be load from {}", path));
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
