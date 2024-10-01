#pragma once


class Transform
{
public:
    Transform(float posX = 0.0f, float posY = 0.0f, float rot = 0.0f, float scaleX = 1.0f, float scaleY = 1.0f)
        : position{posX, posY}, rotation(rot), scale{scaleX, scaleY} {}
    float position[2];
    float rotation;
    float scale[2];
    void SetPosition(float x, float y);
    void SetScale(float x, float y);
};

