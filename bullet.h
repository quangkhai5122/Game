#pragma once

#include "sprite_component.h"
#include "transform_component.h"

class Bullet
{
public:
    Bullet(int x, int y, bool advanced);
    ~Bullet();
    void Update();
    void Render();
    bool IsActive();
    bool CollidePlayer();
private:
    TransformComponent* transform;
    SpriteComponent* sprite;

    bool active;
    int damage;
    int duration;
};