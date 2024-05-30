#pragma once
#include "transform_component.h"
#include "sprite_component.h"
#include "fire_tile.h"
#include "vector"
#include "enemy_health_bar.h"
class Boss
{
public:

    Boss();
    ~Boss();
    bool IsInsideStartingZone(int x, int y);
    void Update();
    void Render();
    void RenderFire();
    void DecHealth(int v);
    bool IsInsideActiveZone();
    bool IsInsideMusicZone();
    bool IsAlive();
    int start_x, start_y;
    TransformComponent* transform;

private:
    void ExecuteSkill();
    void AddAnimations();
    void ExecuteTeleport();
    void ExecuteFirewall();
    void ExecuteShootFireBall();
    void ExecuteSpawnMonster();
    void ExecuteRageMode();
    void UpdateShoot();
    // Skill types
    static const int TELEPORT = 0;
    static const int FIREWALL = 1;
    static const int SHOOT_FIRE_BALL = 2;
    static const int SPAWN_MONSTER = 3;
    //

    int health;

    EnemyHealthBar* health_bar;

    // Duration for using next skill
    int skill_duration;

    // Current skill : [0, 3]
    int cur_skill;

    struct
    {

    } skill_tele;

    struct
    {
        int damage = 3;
        int duration = 700;
        int number = 40;
        std::vector<FireTile*> fire_tiles;
    } skill_fire;

    struct
    {
        int duration = 0;
        int interval = 15;
    } skill_shoot;

    struct
    {
        int number = 4;
    } skill_spawn;

    SpriteComponent* sprite;

    bool rage_mode;
    int rage_mode_cooldown;
    int rage_mode_duration;
};

extern Boss* boss;