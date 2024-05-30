#include "level_manager.h"
#include "player_manager.h"
#include "player_skill_q.h"
#include "player_skill_e.h"
#include "sound_manager.h"
LevelManager::LevelManager()
{
    cur_hp = 0;
    cur_xp = 0;
    cur_attack = 0;
    cur_speed = 0;
    cur_q_cooldown = 0;
    cur_e_duration = 0;

    delta_hp = 20;
    delta_xp = 5;
    delta_attack = 0.7;
    delta_speed = 0.15;
    delta_q_cooldown = -15;
    delta_e_duration = 20;
}
LevelManager::~LevelManager() {}

void LevelManager::Update()
{
    while (player->xp >= player->full_xp)
    {
        player->xp -= player->full_xp;
        LevelUp();
    }
}
void LevelManager::LevelUp()
{
    cur_hp += delta_hp;
    cur_xp += delta_xp;
    cur_attack += delta_attack;
    cur_speed += delta_speed;
    cur_q_cooldown += delta_q_cooldown;
    cur_e_duration += delta_e_duration;

    player->full_health += static_cast<int> (cur_hp);
    cur_hp -= static_cast<int> (cur_hp);
    player->health = player->full_health;

    player->full_xp += static_cast<int> (cur_xp);
    cur_xp -= static_cast<int> (cur_xp);

    player->attack += static_cast<int> (cur_attack);
    cur_attack -= static_cast<int> (cur_attack);

    player->transform->speed += static_cast<int> (cur_speed);
    cur_speed -= static_cast<int> (cur_speed);

    player_skill_q->cooldown_base += static_cast<int> (cur_q_cooldown);
    cur_q_cooldown -= static_cast<int> (cur_q_cooldown);

    player_skill_e->duration_base += static_cast<int> (cur_e_duration);
    cur_e_duration -= static_cast<int> (cur_e_duration);

    sound_manager->PlayLevelUp();
}