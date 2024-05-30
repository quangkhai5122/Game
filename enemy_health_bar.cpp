#include "enemy_health_bar.h"

// TODO: Optimize health bars
EnemyHealthBar::EnemyHealthBar(TransformComponent* _transform, int _w, int _h, int _full_health)
{
    SetTexture();
    transform = _transform;
    src_rect.x = src_rect.y = 0;
    base_src_width = 278;
    src_rect.w = 278;
    src_rect.h = 35;
    base_dest_width = _w;
    dest_rect.w = _w;
    dest_rect.h = _h;
    full_health = _full_health;
    appear_duration = 0;

    dest_rect_bgr.w = _w + 4;
    dest_rect_bgr.h = _h + 4;
}
EnemyHealthBar::~EnemyHealthBar()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(texture_background);
}
void EnemyHealthBar::SetTexture()
{
    texture = TextureManager::LoadTexture("img/enemy/health_bar.png");
    texture_background = TextureManager::LoadTexture("img/enemy/health_bar_background.png");
}

void EnemyHealthBar::Reset(int health)
{
    appear_duration = 80;
    double per = health / (double)full_health;
    dest_rect.w = static_cast<int> (per * base_dest_width);
    src_rect.w = static_cast<int> (per * base_src_width);
}

void EnemyHealthBar::Update(int deltax, int deltay)
{
    dest_rect.x = transform->x + deltax;
    dest_rect.y = transform->y + deltay;
}
void EnemyHealthBar::Draw()
{
    TextureManager::Draw(texture_background, dest_rect_bgr);
    TextureManager::Draw(texture, src_rect, dest_rect);
}
void EnemyHealthBar::Draw(int deltax, int deltay)
{
    if (appear_duration > 0)
    {
        appear_duration--;
        dest_rect.x += deltax;
        dest_rect.y += deltay;
        dest_rect_bgr.x = dest_rect.x - 2;
        dest_rect_bgr.y = dest_rect.y - 2;
        Draw();
    }
}