#pragma once

class LevelComponent
{
public:
    LevelComponent();
    ~LevelComponent();

    void Updated();
private:
    void UpLevel();
    double del_hp, current_hp;
    double del_xp, current_xp;
    double del_attack, current_attack;
    double del_speed, current_speed;
    double del_q_cooldown, current_q_cooldown;
    double del_e_duration, current_e_duration;
};

extern LevelComponent* levelup_manager;