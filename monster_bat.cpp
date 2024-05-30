#include "monster_bat.h"
#include "player_manager.h"
#include "world_map.h"
#include "shooter.h"
#include "sound_manager.h"
MonsterBat::MonsterBat(int x, int y)
{
    movement = new MovementComponent(x, y, 1, 50, 28);
    graphics = new GraphicsComponent("img/Monster/Monster_bat.png", movement, true);
    blood = 50;
    blood_bar = new MonsterHealthBar(movement, 25, 5, blood);
    exp = 2;
    attack = 1;
    attack_intervals = 150;
    attack_max_r = 400;
    attack_min_r = 70;
    move_durative = 50;
    Dx = Dy = 0;
    AddAnimations();
    graphics->ApplyAnimation("walk_right");
    direct = 1;
    sound_manager->PlayMonsterAppear();
}
MonsterBat::~MonsterBat()
{
    delete movement;
    delete graphics;
    delete blood_bar;
}

void MonsterBat::AddAnimations()
{
    Animation walk_right(0, 40, 22, 5, 150);
    Animation walk_left(22, 40, 22, 5, 150);
    graphics->animations_map["walk_right"] = walk_right;
    graphics->animations_map["walk_left"] = walk_left;
}
void MonsterBat::Updated()
{
    // AlreaDy checked IsInsideLivingZone() == true
    if (IsMovingZone())
    {
        if (IsAttackZone()) // Let's attack player
        {
            if (--attack_intervals == 0)
            {
                AttackPlayer();
                attack_intervals = 150;
            }
        }

        if (--move_durative == 0)
        {
            move_durative = 50;
            movement->speed = 1;
            Dx = (rand() % 3) - 1; // [-1, 0, 1]
            Dy = (rand() % 3) - 1; // [-1, 0, 1]
            if (Dx == 1)
            {
                graphics->ApplyAnimation("walk_right");
                direct = 1;
            }
            else if (Dx == -1)
            {
                graphics->ApplyAnimation("walk_left");
                direct = 0;
            }
        }
        else if (move_durative == 10)
            Dx = Dy = 0;


        if (move_durative & 1)
        {
            movement->x += Dx * movement->speed;
            movement->y += Dy * movement->speed;
        }


    }

    graphics->Update();
    blood_bar->Update(13, -15);
}
void MonsterBat::Rendered()
{
    graphics->Draw(-player->xdif, -player->ydif);
    blood_bar->Draw(-player->xdif, -player->ydif);
}

bool MonsterBat::IsLivingZone()
{
    int x = movement->x - player->xdif;
    int y = movement->y - player->ydif;
    return (-1000 < x && x < 2000 && -1000 < y && y < 2000);
}
bool MonsterBat::IsMovingZone()
{
    int x = movement->x - player->xdif;
    int y = movement->y - player->ydif;
    return (-160 < x && x < 928 && -160 < y && y < 768);
}


bool MonsterBat::IsAlives()
{
    return blood > 0;
}

bool MonsterBat::IsAttackZone()
{
    int X = movement->x - player->xdif - 365;
    int Y = movement->y - player->ydif - 300;
    int dist2 = X * X + Y * Y;
    return attack_min_r * attack_min_r <= dist2 && dist2 <= attack_max_r * attack_max_r;
}

void MonsterBat::DecreaseHealth(int v)
{
    blood -= v;
    blood_bar->Reset(blood);
    if (blood <= 0)
        player->xp += exp;
}


void MonsterBat::AttackPlayer()
{
    shoot->AddNewBullets(movement->x + 5, movement->y + 5, false);
}