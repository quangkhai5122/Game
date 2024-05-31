#pragma once
#include "graphics_component.h"
#include "movement_component.h"
class ArrowDirect
{
public:
    int Dx, Dy;

    MovementComponent* movement;
    GraphicsComponent* graphics;

    ArrowDirect();
    ~ArrowDirect();
    void ResetDirection(int ddx, int ddy);
    void Updated();
    void Rendered();
private:
};

extern ArrowDirect* arrow_direct;