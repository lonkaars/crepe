#include "mouseListenerTest.h"

MouseListenerTest::MouseListenerTest(int listenerId) { subscribeEvents(listenerId); }

MouseListenerTest::~MouseListenerTest() { unsubscribeEvents(); }

void MouseListenerTest::onMouseClicked(const MouseClickEvent & event) {
	std::cout << "Mouse clicked at: (" << event.getMousePosition().first << ", "
			  << event.getMousePosition().second << ")" << std::endl;
}

void MouseListenerTest::onMousePressed(const MousePressedEvent & event) {
	std::cout << "Mouse button pressed at: (" << event.getMousePosition().first << ", "
			  << event.getMousePosition().second << ")" << std::endl;
}

void MouseListenerTest::onMouseReleased(const MouseReleasedEvent & event) {
	std::cout << "Mouse button released at: (" << event.getMousePosition().first << ", "
			  << event.getMousePosition().second << ")" << std::endl;
}

void MouseListenerTest::onMouseMoved(const MouseMovedEvent & event) {
	std::cout << "Mouse moved to: (" << event.getMousePosition().first << ", "
			  << event.getMousePosition().second << ")" << std::endl;
}
