#include "enemy_bat.h"
#include "player_manager.h"
#include "world_map.h"
#include "shooter.h"
#include "sound_manager.h"
EnemyBat::EnemyBat(int x, int y)
{
    transform = new TransformComponent(x, y, 1, 50, 28);
    sprite = new SpriteComponent("img/enemy/enemy_bat.png", transform, true);
    health = 50;
    health_bar = new EnemyHealthBar(transform, 25, 5, health);
    xp = 2;
    attack = 1;
    attack_interval = 150;
    attack_max_radius = 400;
    attack_min_radius = 70;
    move_duration = 50;
    dx = dy = 0;
    AddAnimations();
    sprite->ApplyAnimation("walk_right");
    direction = 1;
    sound_manager->PlayMonsterAppear();
}
EnemyBat::~EnemyBat()
{
    delete transform;
    delete sprite;
    delete health_bar;
}

void EnemyBat::AddAnimations()
{
    Animation walk_right(0, 40, 22, 5, 150);
    Animation walk_left(22, 40, 22, 5, 150);
    sprite->animations_map["walk_right"] = walk_right;
    sprite->animations_map["walk_left"] = walk_left;
}
void EnemyBat::Update()
{
    // Already checked IsInsideLivingZone() == true
    if (IsInsideMovingZone())
    {
        if (IsInsideAttackZone()) // Let's attack player
        {
            if (--attack_interval == 0)
            {
                AttackPlayer();
                attack_interval = 150;
            }
        }

        if (--move_duration == 0)
        {
            move_duration = 50;
            transform->speed = 1;
            dx = (rand() % 3) - 1; // [-1, 0, 1]
            dy = (rand() % 3) - 1; // [-1, 0, 1]
            if (dx == 1)
            {
                sprite->ApplyAnimation("walk_right");
                direction = 1;
            }
            else if (dx == -1)
            {
                sprite->ApplyAnimation("walk_left");
                direction = 0;
            }
        }
        else if (move_duration == 10)
            dx = dy = 0;


        if (move_duration & 1)
        {
            transform->x += dx * transform->speed;
            transform->y += dy * transform->speed;
        }


    }

    sprite->Update();
    health_bar->Update(13, -15);
}
void EnemyBat::Render()
{
    sprite->Draw(-player->xdif, -player->ydif);
    health_bar->Draw(-player->xdif, -player->ydif);
}

bool EnemyBat::IsInsideLivingZone()
{
    int x = transform->x - player->xdif;
    int y = transform->y - player->ydif;
    return (-1000 < x && x < 2000 && -1000 < y && y < 2000);
}
bool EnemyBat::IsInsideMovingZone()
{
    int x = transform->x - player->xdif;
    int y = transform->y - player->ydif;
    return (-160 < x && x < 928 && -160 < y && y < 768);
}


bool EnemyBat::IsAlive()
{
    return health > 0;
}

bool EnemyBat::IsInsideAttackZone()
{
    int X = transform->x - player->xdif - 365;
    int Y = transform->y - player->ydif - 300;
    int dist2 = X * X + Y * Y;
    return attack_min_radius * attack_min_radius <= dist2 && dist2 <= attack_max_radius * attack_max_radius;
}

void EnemyBat::DecHealth(int v)
{
    health -= v;
    health_bar->Reset(health);
    if (health <= 0)
        player->xp += xp;
}


void EnemyBat::AttackPlayer()
{
    shooter->AddNewBullet(transform->x + 5, transform->y + 5, false);
}