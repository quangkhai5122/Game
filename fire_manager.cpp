#include "fire_manager.h"
#include "black_boss.h"
#include "knight_manager.h"
#include "anima.h"
FireTile::FireTile(int _damage, int _durative)
{
    damages = _damage;
    durative = _durative;
    damage_durative = 30;
    movement = new MovementComponent(0, 0, 0, 64, 64);
    graphics = new GraphicsComponent("img/gamemenu/fire_tile.png", movement, true);
    AddAnimations();
    graphics->UseAnimation("burn");
}

FireTile::~FireTile()
{
    delete movement;
    delete graphics;
}

void FireTile::AddAnimations()
{
    Animation burn(0, 30, 27, 8, 100);
    graphics->anima_Map["burn"] = burn;
}
void FireTile::Reset(int _damage, int _durative)
{
    damages = _damage;
    durative = _durative;
    movement->x = (rand() % 700) - 400 + boss->begin_x;
    movement->y = (rand() % 700) - 400 + boss->begin_y;
}
void FireTile::Updated()
{
    if (durative == 0)
        return;
    int x0 = movement->x - knight->x_diff;
    int x1 = x0 + 64;
    int y0 = movement->y + 20 - knight->y_diff;
    int y1 = y0 + 54;
    if (knight->CollideWithKnight(x0, y0, x1, y1))
    {
        if (--damage_durative == 0)
        {
            knight->DecreaseHealth(damages);
            damage_durative = 30;
        }
    }
    graphics->Update();
}
void FireTile::Rendered()
{
    if (durative == 0)
        return;
    --durative;
    graphics->Draw(-knight->x_diff, -knight->y_diff);
}