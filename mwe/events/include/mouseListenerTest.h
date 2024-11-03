#pragma once
#include "iMouseListener.h"
#include <iostream>

class MouseListenerTest : public IMouseListener {
public:
	MouseListenerTest(int listenerId);
	~MouseListenerTest();

	void onMouseClicked(const MouseClickEvent & event) override;
	void onMousePressed(const MousePressedEvent & event) override;
	void onMouseReleased(const MouseReleasedEvent & event) override;
	void onMouseMoved(const MouseMovedEvent & event) override;
};
