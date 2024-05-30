#include "fire_tile.h"
#include "boss.h"
#include "player_manager.h"
FireTile::FireTile(int _damage, int _duration)
{
    damage = _damage;
    duration = _duration;
    damage_duration = 30;
    transform = new TransformComponent(0, 0, 0, 64, 64);
    sprite = new SpriteComponent("img/game/fire_tile.png", transform, true);
    AddAnimations();
    sprite->ApplyAnimation("burn");
}

FireTile::~FireTile()
{
    delete transform;
    delete sprite;
}

void FireTile::AddAnimations()
{
    Animation burn(0, 30, 27, 8, 100);
    sprite->animations_map["burn"] = burn;
}
void FireTile::Reset(int _damage, int _duration)
{
    damage = _damage;
    duration = _duration;
    transform->x = (rand() % 700) - 400 + boss->start_x;
    transform->y = (rand() % 700) - 400 + boss->start_y;
}
void FireTile::Update()
{
    if (duration == 0)
        return;
    int x0 = transform->x - player->xdif;
    int x1 = x0 + 64;
    int y0 = transform->y + 20 - player->ydif;
    int y1 = y0 + 54;
    if (player->CollidePlayer(x0, y0, x1, y1))
    {
        if (--damage_duration == 0)
        {
            player->DecHealth(damage);
            damage_duration = 30;
        }
    }
    sprite->Update();
}
void FireTile::Render()
{
    if (duration == 0)
        return;
    --duration;
    sprite->Draw(-player->xdif, -player->ydif);
}