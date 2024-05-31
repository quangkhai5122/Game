#include "monster_health_bar.h"

// TODO: Optimize health bars
MonsterHealthBar::MonsterHealthBar(MovementComponent* _movement, int _w, int _h, int _full_health)
{
    SetTexture();
    movement = _movement;
    source_rect.x = source_rect.y = 0;
    base_source_width = 278;
    source_rect.w = 278;
    source_rect.h = 35;
    base_destina_width = _w;
    destina_rect.w = _w;
    destina_rect.h = _h;
    full_health = _full_health;
    appear_duration = 0;

    destina_rect_bgr.w = _w + 4;
    destina_rect_bgr.h = _h + 4;
}
MonsterHealthBar::~MonsterHealthBar()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture_background);
}
void MonsterHealthBar::SetTexture()
{
    texture = TextureManager::LoadTexture("img/monster/health_bar.png");
    texture_background = TextureManager::LoadTexture("img/monster/health_bar_bkg.png");
}

void MonsterHealthBar::Reset(int health)
{
    appear_duration = 80;
    double per = health / (double)full_health;
    destina_rect.w = static_cast<int> (per * base_destina_width);
    source_rect.w = static_cast<int> (per * base_source_width);
}

void MonsterHealthBar::Update(int deltax, int deltay)
{
    destina_rect.x = movement->x + deltax;
    destina_rect.y = movement->y + deltay;
}
void MonsterHealthBar::Draw()
{
    TextureManager::Draw(texture_background, destina_rect_bgr);
    TextureManager::Draw(texture, source_rect, destina_rect);
}
void MonsterHealthBar::Draw(int deltax, int deltay)
{
    if (appear_duration > 0)
    {
        appear_duration--;
        destina_rect.x += deltax;
        destina_rect.y += deltay;
        destina_rect_bgr.x = destina_rect.x - 2;
        destina_rect_bgr.y = destina_rect.y - 2;
        Draw();
    }
}