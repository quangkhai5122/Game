#pragma once
#include "sprite_component.h"
#include "transform_component.h"
#include "texture_manager.h"
#include <SDL.h>

class PlayerSkillE
{
public:
    PlayerSkillE();
    ~PlayerSkillE();
    void Update();
    void Render();
    void ExecuteSkill();
    int duration; // frames
    int cooldown_base; // frames
    int duration_base; // frames
private:

    SDL_Texture* circle_on, * circle_off;
    SpriteComponent* sprite;
    TransformComponent* transform;
    SDL_Rect circle;
    int cooldown; // frames
};

extern PlayerSkillE* player_skill_e;