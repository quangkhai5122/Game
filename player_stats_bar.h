#pragma once

#include <SDL_ttf.h>
#include "sprite_component.h"
#include "transform_component.h"
#include <string>
#include <algorithm>
class PlayerStatsBar
{
public:
    PlayerStatsBar();
    ~PlayerStatsBar();

    void Update();
    void Render();
    std::string IntToString(int x);
    TTF_Font* font;
    TransformComponent* transform_heart;
    SpriteComponent* sprite_heart;

    TransformComponent* transform_xp;
    SpriteComponent* sprite_xp;

    SDL_Rect box_heart;
    SDL_Rect box_xp;
    SDL_Color Black = { 255, 255, 255 };
    SDL_Surface* surface = NULL;
    SDL_Texture* HP = NULL;
    SDL_Texture* XP = NULL;

};