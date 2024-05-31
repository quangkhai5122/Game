#include "game_func.h"
#include "knight_manager.h"
#include "map.h"
#include "monster_skeleton.h"         
#include "texturer_manager.h"
#include "monster_generator.h"
#include "knight_skill_q.h"
#include "knight_skill_e.h"
#include "arrow_dir.h"
#include "shoot.h"
#include "level_component.h"
#include "black_boss.h"
#include "boss_guide.h"
#include "mixsound_manager.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Window* Game::window = nullptr;
Game::Game() {}
Game::~Game() {}

WorldMap* map;
KnightManager* knight;
KnightSkillQ* knight_skill_q;
KnightSkillE* knight_skill_e;
ArrowDirect* arrow_direct;
MonsterGenerate* enemy_generator;
LevelComponent* level_manager;
Shoot* shooter;
Boss* boss;
BossGuider* boss_guider;
SoundManager* sound_manager;
void Game::Init()
{
    is_running = true;
    knight = new KnightManager("img/knight/knight.png", 365, 300);
    knight_skill_q = new KnightSkillQ();
    knight_skill_e = new KnightSkillE();
    arrow_direct = new ArrowDirect();
    monster_genera = new MonsterGenerate();
    map = new WorldMap();
    shooter = new Shoot();
    level_manager = new LevelComponent();
    boss = new Boss();
    boss_guider = new BossGuider();
    sound_manager = new SoundManager();
    sound_manager->PlayBGM();
}
void Game::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        is_running = false;
        break;
    default:
        break;
    }
    SDL_PumpEvents();

}
void Game::Updated()
{
    enemy_generator->Updated();
    knight->Updated();
    map->Update();
    if (knight->Alive() == false)
        is_running = false;
    knight_skill_q->Updated();
    knight_skill_e->Updated();
    boss->Update();
    level_manager->Updated();
    knight->stats_bar->Updated();
    shooter->Updated();
    boss_guider->Update();
}
void Game::Rendered()
{
    SDL_RenderClear(renderer);
    // Render something here
    map->Render();
    boss->RenderFire();
    knight->Rendered();
    shooter->Rendered();
    enemy_generator->Rendered();
    boss->Render();
    knight->stats_bar->Rendered();
    knight_skill_q->Rendered();
    knight_skill_e->Rendered();
    arrow_direct->Rendered();
    boss_guider->Render();
    sound_manager->Render();

    if (Lost())
        RenderGameOver();
    if (Won())
        RenderGameWon();

    SDL_RenderPresent(renderer);
}
void Game::RenderGameOver()
{
    SDL_Texture* texture = TextureManager::LoadTexture("img/gamemenu/gameover.png");
    SDL_Rect destina_rect_tmp;
    destina_rect_tmp.x = 200;
    destina_rect_tmp.y = 170;
    destina_rect_tmp.w = 400;
    destina_rect_tmp.h = 240;
    TextureManager::Draw(texture, destina_rect_tmp);

    texture = TextureManager::LoadTexture("img/gamemenu/play_again_quit.png");
    destina_rect_tmp.x = 157;
    destina_rect_tmp.y = 420;
    destina_rect_tmp.w = 490;
    destina_rect_tmp.h = 490;
    TextureManager::Draw(texture, destina_rect_tmp);
}
void Game::RenderGameWon()
{
    SDL_Texture* texture = TextureManager::LoadTexture("img/gamemenu/gamewon.png");
    SDL_Rect destina_rect_tmp;
    destina_rect_tmp.x = 100;
    destina_rect_tmp.y = 100;
    destina_rect_tmp.w = 600;
    destina_rect_tmp.h = 340;
    TextureManager::Draw(texture, destina_rect_tmp);

    texture = TextureManager::LoadTexture("img/gamemenu/play_again_quit.png");
    destina_rect_tmp.x = 170;
    destina_rect_tmp.y = 355;
    destina_rect_tmp.w = 490;
    destina_rect_tmp.h = 490;
    TextureManager::Draw(texture, destina_rect_tmp);
}

bool Game::PlayButton(int x, int y)
{
    return 320 <= x && x <= 480
        && 250 <= y && y <= 350;
}
bool Game::HelpButton(int x, int y)
{
    return 320 <= x && x <= 480
        && 365 <= y && y <= 465;
}
bool Game::ExitButton(int x, int y)
{
    return 320 <= x && x <= 480
        && 480 <= y && y <= 580;
}

int Game::UpdateMouse()
{
    int mousex, mousey;

    SDL_PumpEvents();

    Uint32 buttons = SDL_GetMouseState(&mousex, &mousey);

    bool changed = false;
    int play = PlayButton(mousex, mousey);
    int help = HelpButton(mousex, mousey);
    int exit = ExitButton(mousex, mousey);

    if (play != play_button || help != help_button || exit != exit_button)
        changed = true;
    play_button = play;
    help_button = help;
    exit_button = exit;

    if (help && (buttons & SDL_BUTTON_LMASK) != 0)
        return 1;
    if (exit && (buttons & SDL_BUTTON_LMASK) != 0)
        return 2;
    if (play && (buttons & SDL_BUTTON_LMASK) != 0)
        return 3;

    if (!changed)
        return -1;
    return 0;
}

void Game::RendersMenu()
{
    SDL_RenderClear(renderer);
    map->Render();
    SDL_Texture* title = TextureManager::LoadTexture("img/gamemenu/game_title.png");
    SDL_Rect destina, src;
    destina.x = 80;
    destina.y = 50;
    destina.w = 640;
    destina.h = 150;
    TextureManager::Draw(title, destina);

    title = TextureManager::LoadTexture("img/gamemenu/play_button.png");
    src.x = play_button * 150;
    src.y = 0;
    src.w = 150;
    src.h = 98;
    destina.x = 320;
    destina.y = 250;
    destina.w = 160;
    destina.h = 100;
    TextureManager::Draw(title, src, destina);

    title = TextureManager::LoadTexture("img/gamemenu/help_button.png");
    src.x = help_button * 150;
    src.y = 0;
    src.w = 150;
    src.h = 98;
    destina.x = 320;
    destina.y = 365;
    destina.w = 160;
    destina.h = 100;
    TextureManager::Draw(title, src, destina);

    title = TextureManager::LoadTexture("img/gamemenu/exit_button.png");
    src.x = exit_button * 150;
    src.y = 0;
    src.w = 150;
    src.h = 98;
    destina.x = 320;
    destina.y = 480;
    destina.w = 160;
    destina.h = 100;
    TextureManager::Draw(title, src, destina);

    SDL_RenderPresent(renderer);
}

void Game::RendersGuide()
{
    SDL_RenderClear(renderer);
    map->MapGrass();
    SDL_Texture* title = TextureManager::LoadTexture("img/gamemenu/guide.png");
    SDL_Rect destina;
    destina.x = 80;
    destina.y = 110;
    destina.w = 660;
    destina.h = 680;
    TextureManager::Draw(title, destina);

    title = TextureManager::LoadTexture("img/gamemenu/instructions.png");
    destina.x = 280;
    destina.y = 35;
    destina.w = 500;
    destina.h = 550;
    TextureManager::Draw(title, destina);

    title = TextureManager::LoadTexture("img/gamemenu/return_to_menu.png");
    destina.x = 280;
    destina.y = 580;
    destina.w = 250;
    destina.h = 250;
    TextureManager::Draw(title, destina);
    SDL_RenderPresent(renderer);
}

bool Game::Won()
{
    return !boss->IsAlive();
}
bool Game::Lost()
{
    return is_running == false;
}
void Game::Clean()
{
    delete map;
    delete knight;
    delete knight_skill_q;
    delete knight_skill_e;
    delete arrow_direct;
    delete enemy_generator;
    delete level_manager;
    delete shooter;
    delete boss;
    delete boss_guider;
    delete sound_manager;
}