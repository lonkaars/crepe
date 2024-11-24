#include <functional>

#include "Component.h"
#include "api/EventHandler.h"
#include "api/UiObject.h"
namespace crepe {
class Button : public UiObject{
public:
	Button();
	bool interactable = true;
	bool is_toggle = false;
	bool is_pressed = false;
	std::function<void()> on_click;
public:
virtual int get_instances_max() const { return 1; }
};
}
