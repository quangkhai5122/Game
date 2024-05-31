#include <SDL_ttf.h>
#include "game_func.h"
const int FPS = 60;
const int FRAME_MAX_DELAY = 1000 / FPS;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 640;
const Uint8* Game::keyboard_state = SDL_GetKeyboardState(NULL);
Game* game = nullptr;
Uint32 frame_start;
int frame_time;
void Init();
void Clean();
int Menu();
int Help();
int Exit();
int PlayGame();
enum
{
    MENU,
    HELP,
    EXIT,
    PLAYGAME
};
int main(int argc, char* argv[])
{
    Init();

      //0 - Menu.
      //1 - Help.
      //2 - Exit.
      //3 - Play Game.
     
    int type = MENU;

    while (type != EXIT)
    {
        game = new Game();
        switch (type)
        {
        case MENU:
            type = Menu();
            break;
        case HELP:
            type = Help();
            break;
        case EXIT:
            type = Exit();
            break;
        case PLAYGAME:
            type = PlayGame();
            break;
        default:
            break;
        }
        game->Clean();
        delete game;
    }
    Clean();
    return 0;
}
void Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("SDL Failed Initializing...");
        return;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return;
    }

    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }
    Game::window = SDL_CreateWindow("MyfirstGame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    Game::renderer = SDL_CreateRenderer(Game::window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
}
void Clean()
{
    SDL_DestroyWindow(Game::window);
    SDL_DestroyRenderer(Game::renderer);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
}
int Menu()
{
    game->Init();
    game->RendersMenu();
    while (1)
    {
        int state = game->UpdateMouse();
        switch (state)
        {
        case MENU:
            game->RendersMenu();
            break;
        case HELP:
            return HELP;
        case EXIT:
            return EXIT;
        case PLAYGAME:
            return PLAYGAME;
        default:
            break;
        }
    }
    return -1;
}
int Help()
{
    game->Init();
    game->RendersGuide();
    while (1)
    {
        SDL_PumpEvents();
        if (Game::keyboard_state[SDL_SCANCODE_RETURN])
            break;
    }
    return MENU;
}
int Exit()
{
    return EXIT;
}
int PlayGame()
{
    game->Init();
    while (game->Running())
    {
        frame_start = SDL_GetTicks();
        game->HandleEvents();
        game->Updated();
        game->Rendered();
        if (game->Lost())
            break;
        if (game->Won())
            break;
        frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < FRAME_MAX_DELAY)
        {
            SDL_Delay(FRAME_MAX_DELAY - frame_time);
        }
    }
    bool play_again = false;
    while (1)
    {
        SDL_PumpEvents();
        if (Game::keyboard_state[SDL_SCANCODE_RETURN])
        {
            play_again = true;
            break;
        }
        if (Game::keyboard_state[SDL_SCANCODE_ESCAPE])
            break;
    }
    if (play_again)
        return MENU;
    return EXIT;
}