#include "arrow_direction.h"

ArrowDirection::ArrowDirection()
{
    dx = 1;
    dy = 0;
    transform = new TransformComponent(0, 0, 0, 15, 15);
    sprite = new SpriteComponent("img/game/arrow.png", transform, false);
}

ArrowDirection::~ArrowDirection()
{
    delete transform;
    delete sprite;
}
void ArrowDirection::ResetDirection(int ddx, int ddy)
{
    dx = ddx;
    dy = ddy;
}
void ArrowDirection::Update()
{
    if (dx == 1 && dy == 0) // E
    {
        sprite->src_rect.x = 10;
        sprite->src_rect.y = 0;
        sprite->src_rect.w = 10;
        sprite->src_rect.h = 11;

        transform->w = 15;
        transform->h = 15;

        transform->x = 365 + 67;
        transform->y = 300 + 15;
    }
    else if (dx == 0 && dy == 1) // S
    {
        sprite->src_rect.x = 20;
        sprite->src_rect.y = 0;
        sprite->src_rect.w = 11;
        sprite->src_rect.h = 10;

        transform->w = 15;
        transform->h = 15;

        transform->x = 365 + 28;
        transform->y = 300 + 62;
    }
    else if (dx == -1 && dy == 0) // W
    {
        sprite->src_rect.x = 0;
        sprite->src_rect.y = 0;
        sprite->src_rect.w = 10;
        sprite->src_rect.h = 11;

        transform->w = 15;
        transform->h = 15;

        transform->x = 365 - 10;
        transform->y = 300 + 16;
    }
    else if (dx == 0 && dy == -1) // N
    {
        sprite->src_rect.x = 31;
        sprite->src_rect.y = 0;
        sprite->src_rect.w = 11;
        sprite->src_rect.h = 10;

        transform->w = 15;
        transform->h = 15;

        transform->x = 365 + 28;
        transform->y = 300 - 25;

    }
    else if (dx == -1 && dy == -1) // NW
    {
        sprite->src_rect.x = 9;
        sprite->src_rect.y = 11;
        sprite->src_rect.w = 8;
        sprite->src_rect.h = 8;

        transform->w = 10;
        transform->h = 10;

        transform->x = 365 - 5;
        transform->y = 300 - 24;
    }
    else if (dx == -1 && dy == 1) // SW
    {
        sprite->src_rect.x = 18;
        sprite->src_rect.y = 11;
        sprite->src_rect.w = 8;
        sprite->src_rect.h = 8;

        transform->w = 10;
        transform->h = 10;

        transform->x = 365 - 2;
        transform->y = 300 + 62;
    }
    else if (dx == 1 && dy == -1) // NE
    {
        sprite->src_rect.x = 0;
        sprite->src_rect.y = 11;
        sprite->src_rect.w = 8;
        sprite->src_rect.h = 8;

        transform->w = 10;
        transform->h = 10;

        transform->x = 365 + 60;
        transform->y = 300 - 23;
    }
    else if (dx == 1 && dy == 1) // SE
    {
        sprite->src_rect.x = 27;
        sprite->src_rect.y = 11;
        sprite->src_rect.w = 8;
        sprite->src_rect.h = 8;

        transform->w = 10;
        transform->h = 10;

        transform->x = 365 + 60;
        transform->y = 300 + 62;
    }
    sprite->Update();
}

void ArrowDirection::Render()
{
    sprite->Draw();
}