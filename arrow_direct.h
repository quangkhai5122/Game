#pragma once
#include "graphics_component.h"
#include "movement_component.h"
class ArrowDirect
{
public:
    int dx, dy;

    MovementComponent* movement;
    GraphicsComponent* graphics;

    ArrowDirect();
    ~ArrowDirect();
    void ResetDirection(int ddx, int ddy);
    void Update();
    void Render();
private:
};

extern ArrowDirect* arrow_direct;