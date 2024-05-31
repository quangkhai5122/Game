#pragma once
#include <SDL_image.h>
class BossGuider
{
public:
    BossGuider();
    ~BossGuider();
    void Update();
    void Render();
    bool actives;
private:
    SDL_Texture* circl;
    SDL_Rect destina;
};

extern BossGuider* boss_guides;