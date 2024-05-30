#pragma once
#include "transform_component.h"
#include "sprite_component.h"
#include "animation.h"
#include "player_stats_bar.h"
#include "player_skill_q.h"

class PlayerManager
{
public:
    PlayerManager(const char* texture_file, int orig_x, int orig_y);
    ~PlayerManager();

    void AddAnimations();
    void Update();
    void Render();
    bool IsNearPlayer(int x0, int y0, int x1, int y1);
    bool CollidePlayer(int x0, int y0, int x1, int y1);
    bool CollideSwordRight(int x0, int y0, int x1, int y1);
    bool CollideSwordLeft(int x0, int y0, int x1, int y1);
    bool IsAlive();
    void DecHealth(int damage);
    bool IsInsideStartingZone(int x, int y);

    // How far player has moved?
    int xdif, ydif;

    int health, full_health;
    int xp, full_xp;
    int level;

    int attack;

    SpriteComponent* sprite;
    TransformComponent* transform;
    PlayerStatsBar* stats_bar;

    // 1 is right, 0 is left
    bool direction;

    bool is_invincible;
    void SetInvincible(bool invincible);
};
extern PlayerManager* player;