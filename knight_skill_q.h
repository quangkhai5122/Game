#pragma once
#include "graphics_component.h"
#include "movement_component.h"
#include "texturer_manager.h"

class KnightSkillQ
{
public:
    KnightSkillQ();
    ~KnightSkillQ();
    void Updated();
    void Rendered();
    void ExecuteSkill(int dx, int dy);
    void UpdateHitMonster();
    bool IsCollide(int x0, int y0, int x1, int y1);
    int cldown_base; // frames
    int durative_base; // frames
private:

    SDL_Texture* circ_on, * circ_off;
    GraphicsComponent* graphics;
    MovementComponent* movement;
    SDL_Rect circ;
    int cldown; // frames
    int durative; // frames
};

extern KnightSkillQ* knight_skill_q;