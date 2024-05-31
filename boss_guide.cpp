#include "boss_guide.h"
#include "texturer_manager.h"
#include "black_boss.h"
#include "knight_manager.h"
BossGuider::BossGuider()
{
    circl = TextureManager::LoadTexture("img/monster/boss_guider.png");
    destina.w = destina.h = 70;
    actives = false;
}

BossGuider::~BossGuider()
{
    SDL_DestroyTexture(circl);
}
void BossGuider::Update()
{
    if (!actives)
        return;
    int to_x = boss->movement->x + 10 - knight->x_diff;
    int to_y = boss->movement->y + 10 - knight->y_diff;
    if (to_x < 0) to_x = 0;
    if (to_y < 0) to_y = 0;
    if (to_x > 800 - 70) to_x = 800 - 70;
    if (to_y > 640 - 70) to_y = 640 - 70;
    destina.x = to_x;
    destina.y = to_y;
}
void BossGuider::Render()
{
    if (!actives)
        return;
    TextureManager::Draw(circl, destina);
    actives = false;
}