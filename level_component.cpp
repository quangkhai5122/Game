#include "level_component.h"
#include "knight_manager.h"
#include "knight_skill_q.h"
#include "knight_skill_e.h"
#include "mixsound_manager.h"
LevelComponent::LevelComponent()
{
    current_hp = 0;
    current_xp = 0;
    current_attack = 0;
    current_speed = 0;
    current_q_cooldown = 0;
    current_e_duration = 0;

    del_hp = 20;
    del_xp = 5;
    del_attack = 0.7;
    del_speed = 0.15;
    del_q_cooldown = -15;
    del_e_duration = 20;
}
LevelComponent::~LevelComponent() {}

void LevelComponent::Updated()
{
    while (knight->exp >= knight->full_exp)
    {
        knight->exp -= knight->full_exp;
        UpLevel();
    }
}
void LevelComponent::UpLevel()
{
    current_hp += del_hp;
    current_xp += del_xp;
    current_attack += del_attack;
    current_speed += del_speed;
    current_q_cooldown += del_q_cooldown;
    current_e_duration += del_e_duration;

    knight->full_health += static_cast<int> (current_hp);
    current_hp -= static_cast<int> (current_hp);
    knight->health = knight->full_health;

    knight->full_exp += static_cast<int> (current_xp);
    current_xp -= static_cast<int> (current_xp);

    knight->attack += static_cast<int> (current_attack);
    current_attack -= static_cast<int> (current_attack);

    knight->movement->speed += static_cast<int> (current_speed);
    current_speed -= static_cast<int> (current_speed);

    knight_skill_q->cldown_base += static_cast<int> (current_q_cooldown);
    current_q_cooldown -= static_cast<int> (current_q_cooldown);

    knight_skill_e->durative_base += static_cast<int> (current_e_duration);
    current_e_duration -= static_cast<int> (current_e_duration);

    sound_manager->PlayLevelUp();
}