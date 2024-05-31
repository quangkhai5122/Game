#pragma once
#include "graphics_component.h"
#include "movement_component.h"
#include "random"
#include "monster_health_bar.h"

class MonsterSke
{
public:
    MonsterSke(int x, int y);
    ~MonsterSke();

    void AddAnimations();
    void Updated();

    // When player moves, everything gets shifted
    void Render();

    bool IsLivingZone();
    bool IsMovingZone();
    bool CheckMoveCollidion();
    bool TileCollidionEnemy(int x0, int y0, int x1, int y1, int X, int Y);
    bool IsAlives();
    bool IsNearsKnight();
    bool IsNextsToKnight();
    void DecreseHealth(int v);

    GraphicsComponent* graphics;
    MovementComponent* movement;
    MonsterHealthBar* blood_bar;

    int blood;
    int exp;
    int attacks;
    int attack_intervals;
    int attack_r;

private:
    int move_durative;
    int Dx, Dy;
    // 1 is right, 0 is left
    bool direct;
};