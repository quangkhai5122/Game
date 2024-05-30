#pragma once

class LevelManager
{
public:
    LevelManager();
    ~LevelManager();

    void Update();
private:
    void LevelUp();
    double delta_hp, cur_hp;
    double delta_xp, cur_xp;
    double delta_attack, cur_attack;
    double delta_speed, cur_speed;
    double delta_q_cooldown, cur_q_cooldown;
    double delta_e_duration, cur_e_duration;
};

extern LevelManager* level_manager;