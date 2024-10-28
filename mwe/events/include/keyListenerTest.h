#pragma once
#include "iKeyListener.h"
#include <iostream>

class KeyListenerTest : public IKeyListener {
public:
    KeyListenerTest(int listenerId);
    ~KeyListenerTest();

    void onKeyPressed(const KeyPressedEvent& event) override;
    void onKeyReleased(const KeyReleasedEvent& event) override;
};
