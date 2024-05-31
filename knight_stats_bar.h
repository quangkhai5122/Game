#pragma once

#include <SDL_ttf.h>
#include "graphics_component.h"
#include "movement_component.h"
#include <string>
#include <algorithm>
class KnightStatsBar
{
public:
    KnightStatsBar();
    ~KnightStatsBar();

    void Updated();
    void Rendered();
    std::string IntToString(int x);
    TTF_Font* font;
    MovementComponent* movement_heart;
    GraphicsComponent* graphics_heart;

    MovementComponent* movement_xp;
    GraphicsComponent* graphics_xp;

    SDL_Rect box_heart;
    SDL_Rect box_exp;
    SDL_Color Black = { 255, 255, 255 };
    SDL_Surface* surface = NULL;
    SDL_Texture* HP = NULL;
    SDL_Texture* XP = NULL;

};