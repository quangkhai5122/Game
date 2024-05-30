#pragma once
#include "sprite_component.h"
#include "transform_component.h"
#include "random"
#include "enemy_health_bar.h"

class EnemyBat
{
public:
    EnemyBat(int x, int y);
    ~EnemyBat();

    void AddAnimations();
    void Update();

    // When player moves, everything gets shifted
    void Render();

    bool IsInsideLivingZone();
    bool IsInsideMovingZone();
    bool IsAlive();
    bool IsInsideAttackZone();
    void DecHealth(int v);
    void AttackPlayer();

    SpriteComponent* sprite;
    TransformComponent* transform;
    EnemyHealthBar* health_bar;

    int health;
    int xp;
    int attack;
    int attack_interval;
    int attack_max_radius;
    int attack_min_radius;

private:
    int move_duration;
    int dx, dy;
    // 1 is right, 0 is left
    bool direction;
};