#include "ComponentManager.h"
#include "../api/Button.h"
#include "../api/EventManager.h"
#include "../api/Transform.h"
#include "../api/Event.h"

#include "system/InputSystem.h"

using namespace crepe;

InputSystem::InputSystem(ComponentManager &component_manager) 
    : System(component_manager) {
    auto &event_manager = EventManager::get_instance();

    event_manager.subscribe<MouseClickEvent>([this](const MouseClickEvent &event) {
        return this->handle_click(event);
    });

    event_manager.subscribe<MouseMoveEvent>([this](const MouseMoveEvent &event) {
        return this->handle_move(event);
    });
}

void InputSystem::update() {
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

bool InputSystem::handle_move(const MouseMoveEvent &event) {

    ComponentManager &mgr = this->component_manager;

}
