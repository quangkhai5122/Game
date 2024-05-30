#pragma once
#include "sprite_component.h"
#include "transform_component.h"
#include "texture_manager.h"

class PlayerSkillQ
{
public:
    PlayerSkillQ();
    ~PlayerSkillQ();
    void Update();
    void Render();
    void ExecuteSkill(int dx, int dy);
    void UpdateHitEnemy();
    bool IsCollide(int x0, int y0, int x1, int y1);
    int cooldown_base; // frames
    int duration_base; // frames
private:

    SDL_Texture* circle_on, * circle_off;
    SpriteComponent* sprite;
    TransformComponent* transform;
    SDL_Rect circle;
    int cooldown; // frames
    int duration; // frames
};

extern PlayerSkillQ* player_skill_q;