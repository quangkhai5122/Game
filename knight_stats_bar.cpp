#include "knight_stats_bar.h"
#include "game_func.h"
#include "knight_manager.h"
#include <SDL_ttf.h>
KnightStatsBar::KnightStatsBar()
{
    font = TTF_OpenFont("fonts/number_font.ttf", 15);
    if (font == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    movement_heart = new MovementComponent(20, 15, 0, 40, 35);
    graphics_heart = new GraphicsComponent("img/knight/knight_heart.png", movement_heart, false);
    movement_xp = new MovementComponent(20, 60, 0, 40, 35);
    graphics_xp = new GraphicsComponent("img/knight/star_exp.png", movement_xp, false);
    box_heart.x = 70;
    box_heart.y = 20;
    box_heart.w = 150;
    box_heart.h = 30;

    box_exp.x = 80;
    box_exp.y = 67;
    box_exp.w = 110;
    box_exp.h = 30;
}

KnightStatsBar::~KnightStatsBar()
{
    if (surface)
        SDL_FreeSurface(surface);
    if (HP)
        SDL_DestroyTexture(HP);
    if (XP)
        SDL_DestroyTexture(XP);
    delete movement_heart;
    delete movement_xp;
    delete graphics_heart;
    delete graphics_xp;
}
std::string KnightStatsBar::IntToString(int x)
{
    if (x == 0)
        return "0";
    std::string res = "";
    while (x)
    {
        res += (x % 10) + '0';
        x /= 10;
    }
    std::reverse(res.begin(), res.end());
    return res;
}
void KnightStatsBar::Updated()
{
    std::string hp_str = IntToString(knight->health) + "/" + IntToString(knight->full_health);
    std::string xp_str = IntToString(knight->exp) + "/" + IntToString(knight->full_exp);

    surface = TTF_RenderText_Solid(font, hp_str.c_str(), Black);
    HP = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);  

    surface = TTF_RenderText_Solid(font, xp_str.c_str(), Black);
    XP = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);  

    graphics_heart->Update();
    graphics_xp->Update();
}

void KnightStatsBar::Rendered()
{
    SDL_RenderCopy(Game::renderer, HP, NULL, &box_heart);
    SDL_RenderCopy(Game::renderer, XP, NULL, &box_exp);
    graphics_heart->Draw();
    graphics_xp->Draw();
}