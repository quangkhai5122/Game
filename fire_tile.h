#pragma once
#include "sprite_component.h"
#include "transform_component.h"


class FireTile
{
public:
    FireTile(int _damage, int _duration);
    ~FireTile();
    void Reset(int _damage, int _duration);
    void Update();
    void Render();
private:
    void AddAnimations();

    TransformComponent* transform;
    SpriteComponent* sprite;

    int damage;
    int damage_duration;

    int duration;
};