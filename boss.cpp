#include "black_boss.h"
#include <random>
#include "knight_manager.h"
#include "shoot.h"
#include "monster_generator.h"
#include "mixsound_manager.h"
Boss::Boss()
{
    begin_x = (rand() % 2 ? 1 : -1) * (rand() % 5009);
    begin_y = (rand() % 2 ? 1 : -1) * (rand() % 5077);
    cur_skills = 0;
    skill_durations = 200;

    movement = new MovementComponent(begin_x, begin_y, 0, 90, 90);
    graphics = new GraphicsComponent("img/monster/boss.png", movement, true);
    blood = 15000;
    health_bar = new MonsterHealthBar(movement, 80, 7, blood);
    AddAnimations();
    graphics->UseAnimation("walk_right");

    rage_mod = false;
    rage_mod_cooldown = 0; // Thời gian hồi chiêu
    rage_mod_duration = 0; // Thời gian tồn tại chiêu

    skill_fire.fire_tiles.assign(skill_fire.numbers, NULL);
    for (int i = 0; i < skill_fire.numbers; i++)
        skill_fire.fire_tiles[i] = new FireTile(skill_fire.damages, 0);
}

Boss::~Boss()
{
    for (FireTile*& f : skill_fire.fire_tiles)
        delete f;
    delete graphics;
    delete movement;
    delete health_bar;
}

void Boss::Update()
{
    for (FireTile*& f : skill_fire.fire_tiles)
        f->Updated();

    if (!IsActiveZone() || !IsAlive())
        return;
    movement->Update();
    graphics->Update();
    if (rage_mod == true)
    {
        SkillRageMode();
    }
    if (rage_mod_duration == 0)
    {
        if (--skill_durations == 0)
        {
            Skill();
            skill_durations = 400;
            (cur_skills += 1) %= 4;
        }
    }

    UpdateShoot();
    health_bar->Update(-3, -22);
}
void Boss::Render()
{
    if (!IsMusicZone())
    {
        if (sound_manager->IsPlayingBossBGM() == true)
            sound_manager->PlayBGM();
    }
    else
    {
        if (sound_manager->IsPlayingBossBGM() == false)
            sound_manager->PlayBossBGM();
    }
    if (!IsActiveZone() || !IsAlive())
        return;

    graphics->Draw(-knight->x_diff, -knight->y_diff);
    health_bar->Draw(-knight->x_diff, -knight->y_diff);
}
void Boss::RenderFire()
{
    for (FireTile*& f : skill_fire.fire_tiles)
        f->Rendered();
}
bool Boss::IsStartingZone(int x, int y)
{
    int X = (x + knight->x_diff) - begin_x;
    int Y = (y + knight->y_diff) - begin_y;
    return X * X + Y * Y <= 500 * 500;
}

bool Boss::IsActiveZone()
{
    int x = movement->x - knight->x_diff;
    int y = movement->y - knight->y_diff;
    return (-100 < x && x < 900 && -100 < y && y < 700);
}
bool Boss::IsMusicZone()
{
    int x = movement->x - knight->x_diff;
    int y = movement->y - knight->y_diff;
    return (-500 < x && x < 1300 && -500 < y && y < 1100);
}
void Boss::AddAnimations()
{
    Animation walk_left(0, 45, 40, 2, 350);
    Animation walk_right(40, 45, 40, 2, 350);
    graphics->anima_Map["walk_right"] = walk_right;
    graphics->anima_Map["walk_left"] = walk_left;
}

void Boss::DecreaseHealth(int v)
{
    blood -= v;
    health_bar->Reset(blood);
    if (blood < 2500)
        rage_mod = true;
}

void Boss::UpdateShoot()
{
    if (skill_shoots.durations == 0)
        return;
    skill_shoots.durations--;
    if (--skill_shoots.intervals == 0) // Đến lúc bắn 
    {
        skill_shoots.intervals = 20;
        shoot->AddNewBullets(movement->x + 40, movement->y + 40, true);
    }
}
void Boss::Skill()
{
    switch (cur_skills)
    {
    case TELE:
        SkillTeleport();
        break;
    case FIRE:
        SkillFirewall();
        break;
    case FIRE_BALL:
        SkillShootFireBall();
        break;
    case SPAM_MONSTER:
        SkillSpawnMonster();
        break;
    }
}

void Boss::SkillTeleport()
{
    movement->x = (rand() % 450) - 225 + begin_x;
    movement->y = (rand() % 450) - 225 + begin_y;
}
void Boss::SkillFirewall()
{
    for (FireTile*& f : skill_fire.fire_tiles)
        f->Reset(skill_fire.damages, skill_fire.durations);
}
void Boss::SkillShootFireBall()
{
    skill_shoots.durations = 500;
}
void Boss::SkillSpawnMonster()
{
    for (int i = 0; i < skill_spam.number; i++)
    {
        if (monster_genera->bat_list.size() < 30)
            monster_genera->AddNewBatman(movement->x + 40, movement->y + 40);
        if (monster_genera->skeleton_list.size() < 30)
            monster_genera->AddNewSke(movement->x + 40, movement->y + 40);
    }
}
void Boss::SkillRageMode()
{
    if (rage_mod_cooldown == 0)
    {
        rage_mod_cooldown = 1000;
        rage_mod_duration = 500;
        SkillFirewall();
        SkillShootFireBall();
    }
    else rage_mod_cooldown--;
    if (rage_mod_duration > 0)
    {
        rage_mod_duration--;
        if (rage_mod_duration % 50 == 0)
            SkillTeleport();
        if (rage_mod_duration % 300 == 0)
            SkillSpawnMonster();
    }
}
bool Boss::IsAlive()
{
    return blood > 0;
}