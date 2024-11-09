
#include "../system/RenderSystem.h"
#include "../system/ScriptSystem.h"

#include "../facade/SDLContext.h"
#include "LoopManager.h"
#include "LoopTimer.h"

namespace crepe {

void LoopManager::process_input() {
    SDLContext::get_instance().handle_events(this->game_running);
}
void LoopManager::start(){
    this->setup();
    this->loop();
}
void LoopManager::set_running(bool running) { this->game_running = running; }

void LoopManager::fixed_update() {
}

void LoopManager::loop() {
    LoopTimer & timer = LoopTimer::get_instance();
    timer.start();

    while (game_running) {
        timer.update();

        while (timer.get_lag() >= timer.get_fixed_delta_time()) {
            process_input();
            fixed_update();
            timer.advance_fixed_update();
        }

        update();
        render();

        timer.enforce_frame_rate();
    }
}


void LoopManager::setup() {
    this->game_running = true;
    LoopTimer::get_instance().start();
    LoopTimer::get_instance().set_fps(60);
}

void LoopManager::render() {
    if (game_running) {
        RenderSystem::get_instance().update();
    }
}

void LoopManager::update() {
    LoopTimer & timer = LoopTimer::get_instance();
}

} // namespace crepe
