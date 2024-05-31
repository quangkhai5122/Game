#pragma once
#include "graphics_component.h"
#include "movement_component.h"
#include "random"
#include "monster_health_bar.h"

class MonsterBat
{
public:
    MonsterBat(int x, int y);
    ~MonsterBat();

    void AddAnimations();
    void Updated();

    // When player moves, everything gets shifted
    void Rendered();

    bool IsLivingZone();
    bool IsMovingZone();
    bool IsAlives();
    bool IsAttackZone();
    void DecreaseHealth(int v);
    void AttackKnight();

    GraphicsComponent* graphics;
    MovementComponent* movement;
    MonsterHealthBar* blood_bar;

    int blood;
    int exp;
    int attack;
    int attack_intervals;
    int attack_max_r;
    int attack_min_r;

private:
    int move_durative;
    int Dx, Dy;
    // 1 is right, 0 is left
    bool direct;
};