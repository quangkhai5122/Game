#include "sound_manager.h"
#include "texture_manager.h"
SoundManager::SoundManager()
{
    is_playing_boss_bgm = false;
    bgm = Mix_LoadMUS("sfx-bgm/bgm.wav");
    boss_bgm = Mix_LoadMUS("sfx-bgm/boss_bgm.wav");

    level_up = Mix_LoadWAV("sfx-bgm/level_up.wav");
    monster_appear = Mix_LoadWAV("sfx-bgm/monster_appear.wav");
    Q = Mix_LoadWAV("sfx-bgm/Q_slash.wav");
    E = Mix_LoadWAV("sfx-bgm/E_shield.wav");
    shoot = Mix_LoadWAV("sfx-bgm/shoot.wav");
    slash = Mix_LoadWAV("sfx-bgm/slash.wav");
    player_damaged = Mix_LoadWAV("sfx-bgm/player_damaged.wav");

    bgm_on = TextureManager::LoadTexture("img/game/bgm_on.png");
    bgm_off = TextureManager::LoadTexture("img/game/bgm_off.png");
    sfx_on = TextureManager::LoadTexture("img/game/sfx_on.png");
    sfx_off = TextureManager::LoadTexture("img/game/sfx_off.png");
    current = bgm_on;
    dest.x = 700;
    dest.y = 10;
    dest.w = 200;
    dest.h = 200;
}
SoundManager::~SoundManager()
{
    Mix_HaltMusic();
    Mix_FreeMusic(bgm);
    Mix_FreeMusic(boss_bgm);

    Mix_FreeChunk(level_up);
    Mix_FreeChunk(monster_appear);
    Mix_FreeChunk(Q);
    Mix_FreeChunk(E);
    Mix_FreeChunk(shoot);
    Mix_FreeChunk(slash);
    Mix_FreeChunk(player_damaged);

    SDL_DestroyTexture(bgm_on);
    SDL_DestroyTexture(bgm_off);
    SDL_DestroyTexture(sfx_on);
    SDL_DestroyTexture(sfx_off);
    SDL_DestroyTexture(current);
}
void SoundManager::PlayLevelUp()
{
    if (!is_sfx_on)
        return;
    Mix_PlayChannel(-1, level_up, 0);
}
void SoundManager::PlayMonsterAppear()
{
    if (!is_sfx_on)
        return;
    Mix_PlayChannel(-1, monster_appear, 0);
}
void SoundManager::PlayQ()
{
    if (!is_sfx_on)
        return;
    Mix_PlayChannel(-1, Q, 0);
}
void SoundManager::PlayE()
{
    if (!is_sfx_on)
        return;
    Mix_PlayChannel(-1, E, 0);
}
void SoundManager::PlayShoot()
{
    if (!is_sfx_on)
        return;
    Mix_PlayChannel(-1, shoot, 0);
}
void SoundManager::PlaySlash()
{
    if (!is_sfx_on)
        return;
    Mix_PlayChannel(-1, slash, 0);
}
void SoundManager::PlayPlayerDamaged()
{
    if (!is_sfx_on)
        return;
    Mix_PlayChannel(-1, player_damaged, 0);
}
void SoundManager::PlayBossBGM()
{
    if (!is_bgm_on)
        return;
    is_playing_boss_bgm = true;
    Mix_HaltMusic();
    Mix_PlayMusic(boss_bgm, -1);
}
void SoundManager::PlayBGM()
{
    if (!is_bgm_on)
        return;
    is_playing_boss_bgm = false;
    Mix_HaltMusic();
    Mix_PlayMusic(bgm, -1);
}
bool SoundManager::IsPlayingBossBGM()
{
    return is_playing_boss_bgm;
}
void SoundManager::Render()
{
    if (duration > 0)
    {
        duration--;
        TextureManager::Draw(current, dest);
    }
}
void SoundManager::Toggle(int ty)
{
    duration = 100;
    if (ty == 1)
    {
        is_bgm_on ^= 1;
        if (!is_bgm_on)
        {
            Mix_HaltMusic();
            current = bgm_off;
        }
        else
        {
            if (is_playing_boss_bgm)
                PlayBossBGM();
            else
                PlayBGM();
            current = bgm_on;
        }
    }
    else
    {
        is_sfx_on ^= 1;
        if (!is_sfx_on) current = sfx_off;
        else current = sfx_on;
    }
}

void SoundManager::HandleToggle(bool press_K, bool press_L)
{
    if (press_K && !last_press_K)
        Toggle(1);
    if (press_L && !last_press_L)
        Toggle(2);
    last_press_K = press_K;
    last_press_L = press_L;
}