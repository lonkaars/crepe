
#include "ComponentManager.h"
#include "../api/EventManager.h"
#include "../api/Event.h"


#include "system/InputSystem.h"

using namespace crepe;

void InputSystem::update() {
    EventManager &event_mgr = EventManager::get_instance();
    std::vector<SDLContext::EventData> event_list = SDLContext::get_instance().get_events();

    for (const SDLContext::EventData &event : event_list) {
        switch (event.event_type) {
            case SDLContext::Event::KEYDOWN: {
                event_mgr.queue_event<KeyPressEvent>(KeyPressEvent{
                    .repeat = event.key_repeat,
                    .key = event.key,
                });
                break;
            }
            case SDLContext::Event::KEYUP: {
                event_mgr.queue_event<KeyReleaseEvent>(KeyReleaseEvent{
                    .key = event.key,
                });
                break;
            }
            case SDLContext::Event::MOUSEDOWN: {
                event_mgr.queue_event<MousePressEvent>(MousePressEvent{
                    .mouse_x = event.mouse_position.first,
                    .mouse_y = event.mouse_position.second,
                    .button = event.mouse_button,
                });
                last_mouse_down_position = event.mouse_position;
                last_mouse_button = event.mouse_button;
                break;
            }
            case SDLContext::Event::MOUSEUP: {
                MouseReleaseEvent mouse_release_event = MouseReleaseEvent{
                    .mouse_x = event.mouse_position.first,
                    .mouse_y = event.mouse_position.second,
                    .button = event.mouse_button,
                };
                event_mgr.queue_event<MouseReleaseEvent>(mouse_release_event);

                // Calculate deltas for click detection
                int delta_x = event.mouse_position.first - last_mouse_down_position.first;
                int delta_y = event.mouse_position.second - last_mouse_down_position.second;

                if (last_mouse_button == event.mouse_button &&
                    std::abs(delta_x) <= click_tolerance &&
                    std::abs(delta_y) <= click_tolerance) {
                    event_mgr.queue_event<MouseClickEvent>(MouseClickEvent{
                        .mouse_x = event.mouse_position.first,
                        .mouse_y = event.mouse_position.second,
                        .button = event.mouse_button,
                    });

                    handle_click(event);
                }
                break;
            }
            case SDLContext::Event::MOUSEMOVE: {
                event_mgr.queue_event<MouseMoveEvent>(MouseMoveEvent{
                    .mouse_x = event.mouse_position.first,
                    .mouse_y = event.mouse_position.second,
                    .rel_x = event.rel_mouse_move.first,
                    .rel_y = event.rel_mouse_move.second,
                });
                handle_move(event);
                break;
            }
            case SDLContext::Event::MOUSEWHEEL: {
                event_mgr.queue_event<MouseScrollEvent>(MouseScrollEvent{
                    .scroll_x = event.wheel_delta,
                    .scroll_y = 0,
                    .direction = event.wheel_delta,
                });
                break;
            }
            case SDLContext::Event::SHUTDOWN: {
                event_mgr.queue_event<ShutDownEvent>(ShutDownEvent{});
                break;
            }
            default:
                break;
        }
    }
}

void InputSystem::handle_move(const SDLContext::EventData &event_data) {
    ComponentManager &mgr = this->component_manager;

    std::vector<std::reference_wrapper<Button>> buttons = mgr.get_components_by_type<Button>();
    std::vector<std::reference_wrapper<Transform>> transforms = mgr.get_components_by_type<Transform>();

    for (Button &button : buttons) {
        Transform *transform = find_transform_for_button(button, transforms);
        if (!transform)
            continue;

        if (button.interactable && is_mouse_inside_button(event_data, button, *transform)) {
            button.hover = true;
        } else {
            button.hover = false;
        }
    }
}

void InputSystem::handle_click(const SDLContext::EventData &event_data) {
    ComponentManager &mgr = this->component_manager;

    std::vector<std::reference_wrapper<Button>> buttons = mgr.get_components_by_type<Button>();
    std::vector<std::reference_wrapper<Transform>> transforms = mgr.get_components_by_type<Transform>();

    for (Button &button : buttons) {
        Transform *transform = find_transform_for_button(button, transforms);
        if (!transform)
            continue;

        if (button.interactable && is_mouse_inside_button(event_data, button, *transform)) {
            handle_button_press(button);
        }
    }
}

Transform *InputSystem::find_transform_for_button(Button &button, std::vector<std::reference_wrapper<Transform>> &transforms) {
    for (Transform &transform : transforms) {
        if (button.game_object_id == transform.game_object_id) {
            return &transform;
        }
    }
    return nullptr;
}

bool InputSystem::is_mouse_inside_button(const SDLContext::EventData &event_data, const Button &button, const Transform &transform) {
    return event_data.mouse_position.first >= transform.position.x &&
           event_data.mouse_position.first <= transform.position.x + button.width &&
           event_data.mouse_position.second >= transform.position.y &&
           event_data.mouse_position.second <= transform.position.y + button.height;
}

void InputSystem::handle_button_press(Button &button) {
    if (button.is_toggle) {
        if (!button.is_pressed && button.on_click) {
            button.on_click();
        }
        button.is_pressed = !button.is_pressed;
    } else if (button.on_click) {
        button.on_click();
    }
}
