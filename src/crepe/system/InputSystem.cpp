#include "ComponentManager.h"
#include "../api/Button.h"
#include "../api/EventManager.h"
#include "../api/Transform.h"
#include "../facade/SDLContext.h"
#include "../api/Event.h"

#include "system/InputSystem.h"

using namespace crepe;



void InputSystem::update() {
	EventManager& event_mgr = EventManager::get_instance();
    std::vector<SDLContext::EventData> event_list = SDLContext::get_instance().get_events();

    for (SDLContext::EventData event : event_list) {
        switch (event.event_type) {
            case SDLContext::Event::KEYDOWN: {
                event_mgr.queue_event(KeyPressEvent{
                    .key = event.key,
                    .repeat = event.key_repeat,
                });
                break;
            }
            case SDLContext::Event::KEYUP: {
                event_mgr.queue_event(KeyReleaseEvent{
                    .key = event.key,
                });
                break;
            }
            case SDLContext::Event::MOUSEDOWN: {
                event_mgr.queue_event(MousePressEvent{
                    .mouse_x = event.mouse_position.first,
                    .mouse_y = event.mouse_position.second,
                    .button = event.mouse_button,
                });
                break;
            }
            case SDLContext::Event::MOUSEMOVE: {
                event_mgr.queue_event(MouseMoveEvent{
                    .mouse_x = event.mouse_position.first,
                    .mouse_y = event.mouse_position.second,
                    .rel_x = event.rel_mouse_move.first,  
                    .rel_y = event.rel_mouse_move.second,
                });
                break;
            }
            case SDLContext::Event::MOUSEUP: {
                event_mgr.queue_event(MouseReleaseEvent{
                    .mouse_x = event.mouse_position.first,
                    .mouse_y = event.mouse_position.second,
                    .button = event.mouse_button,
                });
                int delta_x = event.mouse_position.first - last_mouse_down_position.first;
                int delta_y = event.mouse_position.second - last_mouse_down_position.second;
                if (last_mouse_button == event.mouse_button &&
                    std::abs(delta_x) <= click_tolerance &&
                    std::abs(delta_y) <= click_tolerance) {
                    event_mgr.queue_event(MouseClickEvent{
                        .mouse_x = event.mouse_position.first,
                        .mouse_y = event.mouse_position.second,
                        .button = event.mouse_button,
                    });
                }
                break;
            }
            case SDLContext::Event::MOUSEWHEEL: {
                event_mgr.queue_event(MouseScrollEvent{
                    .scroll_x = event.mouse_position.first,
                    .scroll_y = event.mouse_position.second,
                    .direction = event.wheel_delta,
                });
                break;
            }
            case SDLContext::Event::SHUTDOWN: {
                event_mgr.queue_event(ShutDownEvent{});
                break;
            }
            default:
                break;
        }
    }
}

bool InputSystem::handle_click(const MouseClickEvent &event) {
    ComponentManager &mgr = this->component_manager;

    std::vector<std::reference_wrapper<Button>> buttons =
        mgr.get_components_by_type<Button>();
	
	std::vector<std::reference_wrapper<Transform>> transforms =
        mgr.get_components_by_type<Transform>();
    for (Button &button : buttons) {
		for(Transform& transform : transforms){
			if(button.game_object_id != transform.game_object_id){continue;}
			if (!button.interactable) {break;}
            if (event.mouse_x >= transform.position.x && event.mouse_x <= transform.position.x + button.width &&
                event.mouse_y >= transform.position.y && event.mouse_y <= transform.position.y + button.height) {
                button.on_click();
            }
		}
    }
    return false;
}

