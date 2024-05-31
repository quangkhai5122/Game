#pragma once
#include "movement_component.h"
#include "graphics_component.h"
#include "fire_manager.h"
#include "vector"
#include "monster_health_bar.h"
class Boss
{
public:

    Boss();
    ~Boss();
    bool IsStartingZone(int x, int y);
    void Update();
    void Render();
    void RenderFire();
    void DecreaseHealth(int v);
    bool IsActiveZone();
    bool IsMusicZone();
    bool IsAlive();
    int begin_x, begin_y;
    MovementComponent* movement;

private:
    void Skill();
    void AddAnimations();
    void SkillTeleport();
    void SkillFirewall();
    void SkillShootFireBall();
    void SkillSpawnMonster();
    void SkillRageMode();
    void UpdateShoot();
    // Skill types
    static const int TELE = 0;
    static const int FIRE = 1;
    static const int FIRE_BALL = 2;
    static const int SPAM_MONSTER = 3;
    //

    int blood;

    MonsterHealthBar* health_bar;

    // Duration for using next skill
    int skill_durations;

    // Current skill : [0, 3]
    int cur_skills;

    struct
    {

    } skill_tele;

    struct
    {
        int damages = 3;
        int durations = 700;
        int numbers = 40;
        std::vector<FireTile*> fire_tiles;
    } skill_fire;

    struct
    {
        int durations = 0;
        int intervals = 15;
    } skill_shoots;

    struct
    {
        int number = 4;
    } skill_spam;

    GraphicsComponent* graphics;

    bool rage_mod;
    int rage_mod_cooldown;
    int rage_mod_duration;
};

extern Boss* boss;