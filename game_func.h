#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

class Game
{
public:
    Game();
    ~Game();

    void Init();
    void HandleEvents();
    void Updated();
    void Rendered();
    void RenderGameOver();
    void RenderGameWon();
    void Clean();
    bool Running() { return is_running; }
    bool Won();
    bool Lost();

    
    int play_button = 0;
    int help_button = 0;
    int exit_button = 0;
    bool PlayButton(int x, int y);
    bool HelpButton(int x, int y);
    bool ExitButton(int x, int y);
    int UpdateMouse();
    void RendersMenu();


    void RendersGuide();


    static SDL_Renderer* renderer;
    static SDL_Window* window;
    static const Uint8* keyboard_state;

private:
    bool is_running;
};