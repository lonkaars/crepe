#include "keyListenerTest.h"

KeyListenerTest::KeyListenerTest(int listenerId) {
    subscribeEvents(listenerId);
}

KeyListenerTest::~KeyListenerTest() {
    unsubscribeEvents();
}

void KeyListenerTest::onKeyPressed(const KeyPressedEvent& event) {
    std::cout << "Key pressed: " << event.getKeyCode() << std::endl;
}

void KeyListenerTest::onKeyReleased(const KeyReleasedEvent& event) {
    std::cout << "Key released: " << event.getKeyCode() << std::endl;
}
