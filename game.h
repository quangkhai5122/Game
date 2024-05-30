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
    void Update();
    void Render();
    void RenderGameOver();
    void RenderGameWon();
    void Clean();
    bool Running() { return is_running; }
    bool Won();
    bool Lost();

    
    int play_button_state = 0;
    int help_button_state = 0;
    int exit_button_state = 0;
    bool InsidePlayButton(int x, int y);
    bool InsideHelpButton(int x, int y);
    bool InsideExitButton(int x, int y);
    int UpdateMouse();
    void RenderMenu();


    void RenderGuide();


    static SDL_Renderer* renderer;
    static SDL_Window* window;
    static const Uint8* keyboard_state;

private:
    bool is_running;
};