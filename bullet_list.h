#pragma once

#include "graphics_component.h"
#include "movement_component.h"

class Bullet
{
public:
    Bullet(int x, int y, bool advance);
    ~Bullet();
    void Updated();
    void Rendered();
    bool IsActives();
    bool CollidesKnight();
private:
    MovementComponent* movement;
    GraphicsComponent* graphics;

    bool isactives;
    int damages;
    int timeduration;
};