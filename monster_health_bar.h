#pragma once

#include "texturer_manager.h"
#include "movement_component.h"
#include <SDL.h>
class MonsterHealthBar
{
private:
    SDL_Texture* texture, * texture_background;
    MovementComponent* movement;
    int appear_duration;
    int base_source_width, base_destina_width;
    int full_health;
public:
    SDL_Rect source_rect, destina_rect, destina_rect_bgr;

    MonsterHealthBar(MovementComponent* _movement, int _w, int _h, int _full_health);
    ~MonsterHealthBar();
    void SetTexture();
    void Reset(int health);
    void Update(int deltax, int deltay);
    void Draw();
    void Draw(int deltax, int deltay);
};