#pragma once
#include "graphics_component.h"
#include "movement_component.h"
#include "texturer_manager.h"
#include <SDL.h>

class KnightSkillE
{
public:
    KnightSkillE();
    ~KnightSkillE();
    void Updated();
    void Rendered();
    void ExecuteSkill();
    int durative; // frames
    int cldown_base; // frames
    int durative_base; // frames
private:

    SDL_Texture* circ_on, * circ_off;
    GraphicsComponent* graphics;
    MovementComponent* movement;
    SDL_Rect circ;
    int cldown; // frames
};

extern KnightSkillE* knight_skill_e;