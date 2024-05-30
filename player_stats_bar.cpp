#include "player_stats_bar.h"
#include "game.h"
#include "player_manager.h"
#include <SDL_ttf.h>
PlayerStatsBar::PlayerStatsBar()
{
    font = TTF_OpenFont("fonts/number_font.ttf", 15);
    if (font == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    }
    transform_heart = new TransformComponent(20, 15, 0, 40, 35);
    sprite_heart = new SpriteComponent("img/player/player_heart.png", transform_heart, false);
    transform_xp = new TransformComponent(20, 60, 0, 40, 35);
    sprite_xp = new SpriteComponent("img/player/star_exp.png", transform_xp, false);
    box_heart.x = 70;
    box_heart.y = 20;
    box_heart.w = 150;
    box_heart.h = 30;

    box_xp.x = 80;
    box_xp.y = 67;
    box_xp.w = 110;
    box_xp.h = 30;
}

PlayerStatsBar::~PlayerStatsBar()
{
    if (surface)
        SDL_FreeSurface(surface);
    if (HP)
        SDL_DestroyTexture(HP);
    if (XP)
        SDL_DestroyTexture(XP);
    delete transform_heart;
    delete transform_xp;
    delete sprite_heart;
    delete sprite_xp;
}
std::string PlayerStatsBar::IntToString(int x)
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
void PlayerStatsBar::Update()
{
    std::string hp_str = IntToString(player->health) + "/" + IntToString(player->full_health);
    std::string xp_str = IntToString(player->xp) + "/" + IntToString(player->full_xp);

    surface = TTF_RenderText_Solid(font, hp_str.c_str(), Black);
    HP = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);  

    surface = TTF_RenderText_Solid(font, xp_str.c_str(), Black);
    XP = SDL_CreateTextureFromSurface(Game::renderer, surface);
    SDL_FreeSurface(surface);  

    sprite_heart->Update();
    sprite_xp->Update();
}

void PlayerStatsBar::Render()
{
    SDL_RenderCopy(Game::renderer, HP, NULL, &box_heart);
    SDL_RenderCopy(Game::renderer, XP, NULL, &box_xp);
    sprite_heart->Draw();
    sprite_xp->Draw();
}