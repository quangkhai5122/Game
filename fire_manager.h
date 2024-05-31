#pragma once
#include "graphics_component.h"
#include "movement_component.h"


class FireTile
{
public:
    FireTile(int _damage, int _duration);
    ~FireTile();
    void Reset(int _damage, int _duration);
    void Updated();
    void Rendered();
private:
    void AddAnimations();

    MovementComponent* movement;
    GraphicsComponent* graphics;

    int damages;
    int damage_durative;

    int durative;
};