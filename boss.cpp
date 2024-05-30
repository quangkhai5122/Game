#include "boss.h"
#include <random>
#include "player_manager.h"
#include "shooter.h"
#include "enemy_generator.h"
#include "sound_manager.h"
Boss::Boss()
{
    start_x = (rand() % 2 ? 1 : -1) * (rand() % 5009);
    start_y = (rand() % 2 ? 1 : -1) * (rand() % 5077);
    cur_skill = 0;
    skill_duration = 200;

    transform = new TransformComponent(start_x, start_y, 0, 90, 90);
    sprite = new SpriteComponent("img/enemy/boss.png", transform, true);
    health = 15000;
    health_bar = new EnemyHealthBar(transform, 80, 7, health);
    AddAnimations();
    sprite->ApplyAnimation("walk_right");

    rage_mode = false;
    rage_mode_cooldown = 0; // Thời gian hồi chiêu
    rage_mode_duration = 0; // Thời gian tồn tại chiêu

    skill_fire.fire_tiles.assign(skill_fire.number, NULL);
    for (int i = 0; i < skill_fire.number; i++)
        skill_fire.fire_tiles[i] = new FireTile(skill_fire.damage, 0);
}

Boss::~Boss()
{
    for (FireTile*& f : skill_fire.fire_tiles)
        delete f;
    delete sprite;
    delete transform;
    delete health_bar;
}

void Boss::Update()
{
    for (FireTile*& f : skill_fire.fire_tiles)
        f->Update();

    if (!IsInsideActiveZone() || !IsAlive())
        return;
    transform->Update();
    sprite->Update();
    if (rage_mode == true)
    {
        ExecuteRageMode();
    }
    if (rage_mode_duration == 0)
    {
        if (--skill_duration == 0)
        {
            ExecuteSkill();
            skill_duration = 400;
            (cur_skill += 1) %= 4;
        }
    }

    UpdateShoot();
    health_bar->Update(-3, -22);
}
void Boss::Render()
{
    if (!IsInsideMusicZone())
    {
        if (sound_manager->IsPlayingBossBGM() == true)
            sound_manager->PlayBGM();
    }
    else
    {
        if (sound_manager->IsPlayingBossBGM() == false)
            sound_manager->PlayBossBGM();
    }
    if (!IsInsideActiveZone() || !IsAlive())
        return;

    sprite->Draw(-player->xdif, -player->ydif);
    health_bar->Draw(-player->xdif, -player->ydif);
}
void Boss::RenderFire()
{
    for (FireTile*& f : skill_fire.fire_tiles)
        f->Render();
}
bool Boss::IsInsideStartingZone(int x, int y)
{
    int X = (x + player->xdif) - start_x;
    int Y = (y + player->ydif) - start_y;
    return X * X + Y * Y <= 500 * 500;
}

bool Boss::IsInsideActiveZone()
{
    int x = transform->x - player->xdif;
    int y = transform->y - player->ydif;
    return (-100 < x && x < 900 && -100 < y && y < 700);
}
bool Boss::IsInsideMusicZone()
{
    int x = transform->x - player->xdif;
    int y = transform->y - player->ydif;
    return (-500 < x && x < 1300 && -500 < y && y < 1100);
}
void Boss::AddAnimations()
{
    Animation walk_left(0, 45, 40, 2, 350);
    Animation walk_right(40, 45, 40, 2, 350);
    sprite->animations_map["walk_right"] = walk_right;
    sprite->animations_map["walk_left"] = walk_left;
}

void Boss::DecHealth(int v)
{
    health -= v;
    health_bar->Reset(health);
    if (health < 2500)
        rage_mode = true;
}

void Boss::UpdateShoot()
{
    if (skill_shoot.duration == 0)
        return;
    skill_shoot.duration--;
    if (--skill_shoot.interval == 0) // Đến lúc bắn 
    {
        skill_shoot.interval = 20;
        shooter->AddNewBullet(transform->x + 40, transform->y + 40, true);
    }
}
void Boss::ExecuteSkill()
{
    switch (cur_skill)
    {
    case TELEPORT:
        ExecuteTeleport();
        break;
    case FIREWALL:
        ExecuteFirewall();
        break;
    case SHOOT_FIRE_BALL:
        ExecuteShootFireBall();
        break;
    case SPAWN_MONSTER:
        ExecuteSpawnMonster();
        break;
    }
}

void Boss::ExecuteTeleport()
{
    transform->x = (rand() % 450) - 225 + start_x;
    transform->y = (rand() % 450) - 225 + start_y;
}
void Boss::ExecuteFirewall()
{
    for (FireTile*& f : skill_fire.fire_tiles)
        f->Reset(skill_fire.damage, skill_fire.duration);
}
void Boss::ExecuteShootFireBall()
{
    skill_shoot.duration = 500;
}
void Boss::ExecuteSpawnMonster()
{
    for (int i = 0; i < skill_spawn.number; i++)
    {
        if (enemy_generator->bat_container.size() < 30)
            enemy_generator->AddNewBat(transform->x + 40, transform->y + 40);
        if (enemy_generator->skeleton_container.size() < 30)
            enemy_generator->AddNewSkeleton(transform->x + 40, transform->y + 40);
    }
}
void Boss::ExecuteRageMode()
{
    if (rage_mode_cooldown == 0)
    {
        rage_mode_cooldown = 1000;
        rage_mode_duration = 500;
        ExecuteFirewall();
        ExecuteShootFireBall();
    }
    else rage_mode_cooldown--;
    if (rage_mode_duration > 0)
    {
        rage_mode_duration--;
        if (rage_mode_duration % 50 == 0)
            ExecuteTeleport();
        if (rage_mode_duration % 300 == 0)
            ExecuteSpawnMonster();
    }
}
bool Boss::IsAlive()
{
    return health > 0;
}