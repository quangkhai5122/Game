#include "player_skill_q.h"
#include "player_manager.h"
#include "enemy_generator.h"
#include "point_2d.h"
#include "boss.h"
#include "sound_manager.h"
PlayerSkillQ::PlayerSkillQ()
{
    cooldown = 0; 
    duration = 0;
    cooldown_base = 300; //Thoi gian hoi chieu
    duration_base = 150; //Thoi gian ton tai chieu

    circle_on = TextureManager::LoadTexture("img/player/q_circle_on.png");
    circle_off = TextureManager::LoadTexture("img/player/q_circle_off.png");
    circle.x = 580, circle.y = 530;
    circle.w = circle.h = 80;

    transform = new TransformComponent(0, 0, 6, 0, 0);
    sprite = new SpriteComponent("img/player/q_animation.png", transform, false);

}

PlayerSkillQ::~PlayerSkillQ()
{
    delete transform;
    delete sprite;
    SDL_DestroyTexture(circle_on);
    SDL_DestroyTexture(circle_off);
}

void PlayerSkillQ::Update()
{
    if (duration > 0)
    {
        transform->Update();
        sprite->Update();
        UpdateHitEnemy();
    }
}
void PlayerSkillQ::Render()
{
    if (cooldown == 0)
        TextureManager::Draw(circle_on, circle);
    else
    {
        cooldown--;
        TextureManager::Draw(circle_off, circle);
    }
    if (duration > 0)
    {
        duration--;
        sprite->Draw(-player->xdif, -player->ydif);
    }
}
void PlayerSkillQ::ExecuteSkill(int dx, int dy)
{

    if (cooldown == 0 || cooldown >= 150)
    {
        if (player->direction)
            player->sprite->ApplyAnimation("sword_right");
        else
            player->sprite->ApplyAnimation("sword_left");
    }
    if (cooldown > 0)
        return;
    sound_manager->PlayQ();
    duration = duration_base;
    cooldown = cooldown_base;
    transform->vx = dx;
    transform->vy = dy;
    if (dx == 1 && dy == 0) // E
    {
        sprite->src_rect.x = 0;
        sprite->src_rect.y = 45;
        sprite->src_rect.w = 16;
        sprite->src_rect.h = 32;

        transform->w = 20;
        transform->h = 70;

        transform->x = 365 + player->xdif + 50;
        transform->y = 300 + player->ydif - 10;
    }
    else if (dx == 0 && dy == 1) // S
    {
        sprite->src_rect.x = 0;
        sprite->src_rect.y = 29;
        sprite->src_rect.w = 32;
        sprite->src_rect.h = 16;

        transform->w = 70;
        transform->h = 20;

        transform->x = 365 + player->xdif;
        transform->y = 300 + player->ydif + 40;
    }
    else if (dx == -1 && dy == 0) // W
    {
        sprite->src_rect.x = 16;
        sprite->src_rect.y = 45;
        sprite->src_rect.w = 16;
        sprite->src_rect.h = 32;

        transform->w = 20;
        transform->h = 70;

        transform->x = 365 + player->xdif;
        transform->y = 300 + player->ydif - 10;
    }
    else if (dx == 0 && dy == -1) // N
    {
        sprite->src_rect.x = 32;
        sprite->src_rect.y = 29;
        sprite->src_rect.w = 32;
        sprite->src_rect.h = 16;

        transform->w = 70;
        transform->h = 20;

        transform->x = 365 + player->xdif;
        transform->y = 300 + player->ydif - 30;

    }
    else if (dx == -1 && dy == -1) // NW
    {
        sprite->src_rect.x = 29;
        sprite->src_rect.y = 0;
        sprite->src_rect.w = 29;
        sprite->src_rect.h = 29;

        transform->w = 60;
        transform->h = 60;

        transform->x = 365 + player->xdif - 28;
        transform->y = 300 + player->ydif - 28;
    }
    else if (dx == -1 && dy == 1) // SW
    {
        sprite->src_rect.x = 87;
        sprite->src_rect.y = 0;
        sprite->src_rect.w = 29;
        sprite->src_rect.h = 29;

        transform->w = 60;
        transform->h = 60;

        transform->x = 365 + player->xdif - 30;
        transform->y = 300 + player->ydif + 30;
    }
    else if (dx == 1 && dy == -1) // NE
    {
        sprite->src_rect.x = 0;
        sprite->src_rect.y = 0;
        sprite->src_rect.w = 29;
        sprite->src_rect.h = 29;

        transform->w = 60;
        transform->h = 60;

        transform->x = 365 + player->xdif + 30;
        transform->y = 300 + player->ydif - 30;
    }
    else if (dx == 1 && dy == 1) // SE
    {
        sprite->src_rect.x = 58;
        sprite->src_rect.y = 0;
        sprite->src_rect.w = 29;
        sprite->src_rect.h = 29;

        transform->w = 60;
        transform->h = 60;

        transform->x = 365 + player->xdif + 30;
        transform->y = 300 + player->ydif + 30;
    }
}


bool PlayerSkillQ::IsCollide(int x0, int y0, int x1, int y1)
{
    Point<int> rect_s(x0, y0), rect_e(x1, y1);
    Point<int> s, e, s1, e1;
    int dx = transform->vx, dy = transform->vy;
    int curx = transform->x, cury = transform->y;
    if (dx == 1 && dy == 0) // E
    {
        s = Point<int>(curx, cury);
        e = Point<int>(curx, cury + 70);
        s1 = Point<int>(curx + 18, cury);
        e1 = Point<int>(curx + 18, cury + 70);
    }
    else if (dx == 0 && dy == 1) // S
    {
        s = Point<int>(curx, cury);
        e = Point<int>(curx + 70, cury);
        s1 = Point<int>(curx, cury + 20);
        e1 = Point<int>(curx + 70, cury + 20);
    }
    else if (dx == -1 && dy == 0) // W
    {
        s = Point<int>(curx + 2, cury);
        e = Point<int>(curx + 2, cury + 70);
        s1 = Point<int>(curx + 20, cury);
        e1 = Point<int>(curx + 20, cury + 70);
    }
    else if (dx == 0 && dy == -1) // N
    {
        s = Point<int>(curx, cury + 2);
        e = Point<int>(curx + 70, cury + 2);
        s1 = Point<int>(curx, cury + 22);
        e1 = Point<int>(curx + 70, cury + 22);
    }
    else if (dx == -1 && dy == -1) // NW
    {
        s = Point<int>(curx, cury + 45);
        e = Point<int>(curx + 45, cury);
        s1 = Point<int>(curx + 15, cury + 60);
        e1 = Point<int>(curx + 60, cury + 15);
    }
    else if (dx == -1 && dy == 1) // SW
    {
        s = Point<int>(curx + 15, cury);
        e = Point<int>(curx + 60, cury + 45);
        s1 = Point<int>(curx, cury + 15);
        e1 = Point<int>(curx + 45, cury + 60);
    }
    else if (dx == 1 && dy == -1) // NE
    {
        s = Point<int>(curx + 15, cury);
        e = Point<int>(curx + 60, cury + 45);
        s1 = Point<int>(curx, cury + 15);
        e1 = Point<int>(curx + 45, cury + 60);
    }
    else if (dx == 1 && dy == 1) // SE
    {
        s = Point<int>(curx, cury + 45);
        e = Point<int>(curx + 45, cury);
        s1 = Point<int>(curx + 15, cury + 60);
        e1 = Point<int>(curx + 60, cury + 15);
    }
    return SegInterRectangle(rect_s, rect_e, s, e) || SegInterRectangle(rect_s, rect_e, s1, e1);
}
void PlayerSkillQ::UpdateHitEnemy()
{
    for (EnemySkeleton*& e : enemy_generator->skeleton_container)
        if (e->IsInsideMovingZone())
        {
            int x0 = e->transform->x + 20;
            int y0 = e->transform->y;
            int x1 = x0 + 40;
            int y1 = y0 + 30;
            if (IsCollide(x0, y0, x1, y1))
            {
                e->DecHealth(2 * player->attack);
            }
        }
    for (EnemyBat*& e : enemy_generator->bat_container)
        if (e->IsInsideMovingZone())
        {
            int x0 = e->transform->x + 14;
            int y0 = e->transform->y + 5;
            int x1 = x0 + 25;
            int y1 = y0 + 20;
            if (IsCollide(x0, y0, x1, y1))
            {
                e->DecHealth(2 * player->attack);
            }
        }
    if (boss->IsInsideActiveZone())
    {
        int x0 = boss->transform->x + 20;
        int y0 = boss->transform->y;
        int x1 = x0 + 60;
        int y1 = y0 + 90;
        if (IsCollide(x0, y0, x1, y1))
        {
            boss->DecHealth(player->attack);
        }
    }
}