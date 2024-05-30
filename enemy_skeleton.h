#pragma once
#include "sprite_component.h"
#include "transform_component.h"
#include "random"
#include "enemy_health_bar.h"

class EnemySkeleton
{
public:
    EnemySkeleton(int x, int y);
    ~EnemySkeleton();

    void AddAnimations();
    void Update();

    // When player moves, everything gets shifted
    void Render();

    bool IsInsideLivingZone();
    bool IsInsideMovingZone();
    bool CheckMoveCollide();
    bool TileCollideEnemy(int x0, int y0, int x1, int y1, int X, int Y);
    bool IsAlive();
    bool IsNearPlayer();
    bool IsNextToPlayer();
    void DecHealth(int v);

    SpriteComponent* sprite;
    TransformComponent* transform;
    EnemyHealthBar* health_bar;

    int health;
    int xp;
    int attack;
    int attack_interval;
    int attack_radius;

private:
    int move_duration;
    int dx, dy;
    // 1 is right, 0 is left
    bool direction;
};