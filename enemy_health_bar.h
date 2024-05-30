#pragma once

#include "texture_manager.h"
#include "transform_component.h"
#include <SDL.h>
class EnemyHealthBar
{
private:
    SDL_Texture* texture, * texture_background;
    TransformComponent* transform;
    int appear_duration;
    int base_src_width, base_dest_width;
    int full_health;
public:
    SDL_Rect src_rect, dest_rect, dest_rect_bgr;

    EnemyHealthBar(TransformComponent* _transform, int _w, int _h, int _full_health);
    ~EnemyHealthBar();
    void SetTexture();
    void Reset(int health);
    void Update(int deltax, int deltay);
    void Draw();
    void Draw(int deltax, int deltay);
};