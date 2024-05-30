#include "boss_guider.h"
#include "texture_manager.h"
#include "boss.h"
#include "player_manager.h"
BossGuider::BossGuider()
{
    circle = TextureManager::LoadTexture("img/enemy/boss_guider_circle.png");
    dest.w = dest.h = 70;
    active = false;
}

BossGuider::~BossGuider()
{
    SDL_DestroyTexture(circle);
}
void BossGuider::Update()
{
    if (!active)
        return;
    int to_x = boss->transform->x + 10 - player->xdif;
    int to_y = boss->transform->y + 10 - player->ydif;
    if (to_x < 0) to_x = 0;
    if (to_y < 0) to_y = 0;
    if (to_x > 800 - 70) to_x = 800 - 70;
    if (to_y > 640 - 70) to_y = 640 - 70;
    dest.x = to_x;
    dest.y = to_y;
}
void BossGuider::Render()
{
    if (!active)
        return;
    TextureManager::Draw(circle, dest);
    active = false;
}