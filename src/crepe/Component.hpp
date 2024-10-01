#pragma once
class Component {
public:
    bool active;
    Component() : active(true) {}
    virtual ~Component() {}
};
