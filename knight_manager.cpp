#include "knight_manager.h"
#include "texturer_manager.h"
#include "knight_skill_e.h"
#include "mixsound_manager.h"
KnightManager::KnightManager(const char* texture_file, int orig_x, int orig_y)
{
    x_diff = y_diff = 0;
    movement = new MovementComponent(orig_x, orig_y, 3, 70, 45);
    graphics = new GraphicsComponent(texture_file, movement, true);
    stats_bar = new KnightStatsBar();
    dir = 1;
    health = 100;
    full_health = 100;
    exp = 0;
    full_exp = 10;
    level = 1;
    attack = 6;
    AddAnima();
    graphics->UseAnimation("idle_right");
    is_invincible = false;

}
KnightManager::~KnightManager()
{
    delete graphics;
    delete movement;
    delete stats_bar;
}
void KnightManager::Updated()
{
    health = std::max(health, 0);
    graphics->Update();
}

void KnightManager::Rendered()
{
    graphics->Draw();
}

void KnightManager::AddAnima()
{
    Animation walk_right(0, 33, 21, 4, 200);
    Animation walk_left(21, 33, 21, 4, 200);
    Animation sword_right(42, 33, 21, 3, 100);
    Animation sword_left(63, 33, 21, 3, 100);
    graphics->anima_Map["idle_right"] = walk_right;
    graphics->anima_Map["idle_left"] = walk_left;
    graphics->anima_Map["walk_right"] = walk_right;
    graphics->anima_Map["walk_left"] = walk_left;
    graphics->anima_Map["sword_right"] = sword_right;
    graphics->anima_Map["sword_left"] = sword_left;
}

bool KnightManager::IsNearKnight(int x0, int y0, int x1, int y1)
{
    return (std::max(x0, 385) <= std::min(x1, 415))
        && (std::max(y0, 305) <= std::min(y1, 355));
}

bool KnightManager::CollideWithKnight(int x0, int y0, int x1, int y1)
{
    return (std::max(x0, 390) <= std::min(x1, 410))
        && (std::max(y0, 305) <= std::min(y1, 350));
}

bool KnightManager::CollidesSwordR(int x0, int y0, int x1, int y1)
{
    return (std::max(x0, 415) <= std::min(x1, 420))
        && (std::max(y0, 305) <= std::min(y1, 350));
}
bool KnightManager::CollidesSwordL(int x0, int y0, int x1, int y1)
{
    return (std::max(x0, 380) <= std::min(x1, 385))
        && (std::max(y0, 305) <= std::min(y1, 350));
}

bool KnightManager::Alive()
{
    return health > 0;
}

void KnightManager::SetInvincible(bool invincible)
{
    is_invincible = invincible;
}

void KnightManager::DecreaseHealth(int damage)
{
    if (!is_invincible) {
        knight->health -= damage;
        sound_manager->PlayPlayerDamaged();
    }
}

bool KnightManager::IsStartingZone(int x, int y)
{
    return ((x + knight->x_diff) <= 450)
        && ((x + knight->x_diff) >= 200)
        && ((y + knight->y_diff) <= 400)
        && ((y + knight->y_diff) >= 150);
}