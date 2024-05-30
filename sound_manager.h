#pragma once
#include <SDL_mixer.h>
#include <SDL_image.h>
class SoundManager
{
public:
    SoundManager();
    ~SoundManager();
    void PlayLevelUp();
    void PlayMonsterAppear();
    void PlayQ();
    void PlayE();
    void PlayShoot();
    void PlaySlash();
    void PlayPlayerDamaged();
    void PlayBossBGM();
    void PlayBGM();
    bool IsPlayingBossBGM();
    void Toggle(int ty);
    void Render();
    void HandleToggle(bool press_K, bool press_L);
private:
    bool is_playing_boss_bgm;

    Mix_Music* bgm = NULL;
    Mix_Music* boss_bgm = NULL;

    //The sound effects that will be used
    Mix_Chunk* level_up = NULL;
    Mix_Chunk* monster_appear = NULL;
    Mix_Chunk* Q = NULL;
    Mix_Chunk* E = NULL;
    Mix_Chunk* shoot = NULL;
    Mix_Chunk* slash = NULL;
    Mix_Chunk* player_damaged = NULL;

    SDL_Texture* bgm_on;
    SDL_Texture* bgm_off;
    SDL_Texture* sfx_on;
    SDL_Texture* sfx_off;
    SDL_Texture* current;
    int duration = 0;
    bool is_bgm_on = true;
    bool is_sfx_on = true;
    SDL_Rect dest;

    bool last_press_K = false;
    bool last_press_L = false;
};

extern SoundManager* sound_manager;