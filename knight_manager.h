#pragma once
#include "movement_component.h"
#include "graphics_component.h"
#include "anima.h"
#include "knight_stats_bar.h"
#include "knight_skill_q.h"

class KnightManager
{
public:
    KnightManager(const char* texture_file, int orig_x, int orig_y);
    ~KnightManager();

    void AddAnima();
    void Updated();
    void Rendered();
    bool IsNearKnight(int x0, int y0, int x1, int y1);
    bool CollideWithKnight(int x0, int y0, int x1, int y1);
    bool CollidesSwordR(int x0, int y0, int x1, int y1);
    bool CollidesSwordL(int x0, int y0, int x1, int y1);
    bool Alive();
    void DecreaseHealth(int damage);
    bool IsStartingZone(int x, int y);

    // How far player has moved?
    int x_diff, y_diff;

    int health, full_health;
    int exp, full_exp;
    int level;

    int attack;

    GraphicsComponent* graphics;
    MovementComponent* movement;
    KnightStatsBar* stats_bar;

    // 1 is right, 0 is left
    bool dir;

    bool is_invincible;
    void SetInvincible(bool invincible);
};
extern KnightManager* knight;