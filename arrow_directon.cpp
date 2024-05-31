#include "arrow_dir.h"

ArrowDirect::ArrowDirect()
{
    Dx = 1;
    Dy = 0;
    movement = new MovementComponent(0, 0, 0, 15, 15);
    graphics = new GraphicsComponent("img/gamemenu/arrow.png", movement, false);
}

ArrowDirect::~ArrowDirect()
{
    delete movement;
    delete graphics;
}
void ArrowDirect::ResetDirection(int dDx, int dDy)
{
    Dx = dDx;
    Dy = dDy;
}
void ArrowDirect::Updated()
{
    if (Dx == 1 && Dy == 0) // E
    {
        graphics->source_rect.x = 10;
        graphics->source_rect.y = 0;
        graphics->source_rect.w = 10;
        graphics->source_rect.h = 11;

        movement->w = 15;
        movement->h = 15;

        movement->x = 365 + 67;
        movement->y = 300 + 15;
    }
    else if (Dx == 0 && Dy == 1) // S
    {
        graphics->source_rect.x = 20;
        graphics->source_rect.y = 0;
        graphics->source_rect.w = 11;
        graphics->source_rect.h = 10;

        movement->w = 15;
        movement->h = 15;

        movement->x = 365 + 28;
        movement->y = 300 + 62;
    }
    else if (Dx == -1 && Dy == 0) // W
    {
        graphics->source_rect.x = 0;
        graphics->source_rect.y = 0;
        graphics->source_rect.w = 10;
        graphics->source_rect.h = 11;

        movement->w = 15;
        movement->h = 15;

        movement->x = 365 - 10;
        movement->y = 300 + 16;
    }
    else if (Dx == 0 && Dy == -1) // N
    {
        graphics->source_rect.x = 31;
        graphics->source_rect.y = 0;
        graphics->source_rect.w = 11;
        graphics->source_rect.h = 10;

        movement->w = 15;
        movement->h = 15;

        movement->x = 365 + 28;
        movement->y = 300 - 25;

    }
    else if (Dx == -1 && Dy == -1) // NW
    {
        graphics->source_rect.x = 9;
        graphics->source_rect.y = 11;
        graphics->source_rect.w = 8;
        graphics->source_rect.h = 8;

        movement->w = 10;
        movement->h = 10;

        movement->x = 365 - 5;
        movement->y = 300 - 24;
    }
    else if (Dx == -1 && Dy == 1) // SW
    {
        graphics->source_rect.x = 18;
        graphics->source_rect.y = 11;
        graphics->source_rect.w = 8;
        graphics->source_rect.h = 8;

        movement->w = 10;
        movement->h = 10;

        movement->x = 365 - 2;
        movement->y = 300 + 62;
    }
    else if (Dx == 1 && Dy == -1) // NE
    {
        graphics->source_rect.x = 0;
        graphics->source_rect.y = 11;
        graphics->source_rect.w = 8;
        graphics->source_rect.h = 8;

        movement->w = 10;
        movement->h = 10;

        movement->x = 365 + 60;
        movement->y = 300 - 23;
    }
    else if (Dx == 1 && Dy == 1) // SE
    {
        graphics->source_rect.x = 27;
        graphics->source_rect.y = 11;
        graphics->source_rect.w = 8;
        graphics->source_rect.h = 8;

        movement->w = 10;
        movement->h = 10;

        movement->x = 365 + 60;
        movement->y = 300 + 62;
    }
    graphics->Update();
}

void ArrowDirect::Rendered()
{
    graphics->Draw();
}