#include "knight_skill_q.h"
#include "knight_manager.h"
#include "monster_generator.h"
#include "pointOxy.h"
#include "black_boss.h"
#include "mixsound_manager.h"
KnightSkillQ::KnightSkillQ()
{
    cldown = 0; 
    durative = 0;
    cldown_base = 300; //Thoi gian hoi chieu
    durative_base = 150; //Thoi gian ton tai chieu

    circ_on = TextureManager::LoadTexture("img/knight/q_circon.png");
    circ_off = TextureManager::LoadTexture("img/knight/q_circoff.png");
    circ.x = 580, circ.y = 530;
    circ.w = circ.h = 80;

    movement = new MovementComponent(0, 0, 6, 0, 0);
    graphics = new GraphicsComponent("img/knight/q_anima.png", movement, false);

}

KnightSkillQ::~KnightSkillQ()
{
    delete movement;
    delete graphics;
    SDL_DestroyTexture(circ_on);
    SDL_DestroyTexture(circ_off);
}

void KnightSkillQ::Updated()
{
    if (durative > 0)
    {
        movement->Update();
        graphics->Update();
        UpdateHitMonster();
    }
}
void KnightSkillQ::Rendered()
{
    if (cldown == 0)
        TextureManager::Draw(circ_on, circ);
    else
    {
        cldown--;
        TextureManager::Draw(circ_off, circ);
    }
    if (durative > 0)
    {
        durative--;
        graphics->Draw(-knight->x_diff, -knight->y_diff);
    }
}
void KnightSkillQ::ExecuteSkill(int dx, int dy)
{

    if (cldown == 0 || cldown >= 150)
    {
        if (knight->dir)
            knight->graphics->UseAnimation("sword_right");
        else
            knight->graphics->UseAnimation("sword_left");
    }
    if (cldown > 0)
        return;
    sound_manager->PlayQ();
    durative = durative_base;
    cldown = cldown_base;
    movement->velocity_x = dx;
    movement->velocity_y = dy;
    if (dx == 1 && dy == 0) // E
    {
        graphics->source_rect.x = 0;
        graphics->source_rect.y = 45;
        graphics->source_rect.w = 16;
        graphics->source_rect.h = 32;

        movement->w = 20;
        movement->h = 70;

        movement->x = 365 + knight->x_diff + 50;
        movement->y = 300 + knight->y_diff - 10;
    }
    else if (dx == 0 && dy == 1) // S
    {
        graphics->source_rect.x = 0;
        graphics->source_rect.y = 29;
        graphics->source_rect.w = 32;
        graphics->source_rect.h = 16;

        movement->w = 70;
        movement->h = 20;

        movement->x = 365 + knight->x_diff;
        movement->y = 300 + knight->y_diff + 40;
    }
    else if (dx == -1 && dy == 0) // W
    {
        graphics->source_rect.x = 16;
        graphics->source_rect.y = 45;
        graphics->source_rect.w = 16;
        graphics->source_rect.h = 32;

        movement->w = 20;
        movement->h = 70;

        movement->x = 365 + knight->x_diff;
        movement->y = 300 + knight->y_diff - 10;
    }
    else if (dx == 0 && dy == -1) // N
    {
        graphics->source_rect.x = 32;
        graphics->source_rect.y = 29;
        graphics->source_rect.w = 32;
        graphics->source_rect.h = 16;

        movement->w = 70;
        movement->h = 20;

        movement->x = 365 + knight->x_diff;
        movement->y = 300 + knight->y_diff - 30;

    }
    else if (dx == -1 && dy == -1) // NW
    {
        graphics->source_rect.x = 29;
        graphics->source_rect.y = 0;
        graphics->source_rect.w = 29;
        graphics->source_rect.h = 29;

        movement->w = 60;
        movement->h = 60;

        movement->x = 365 + knight->x_diff - 28;
        movement->y = 300 + knight->y_diff - 28;
    }
    else if (dx == -1 && dy == 1) // SW
    {
        graphics->source_rect.x = 87;
        graphics->source_rect.y = 0;
        graphics->source_rect.w = 29;
        graphics->source_rect.h = 29;

        movement->w = 60;
        movement->h = 60;

        movement->x = 365 + knight->x_diff - 30;
        movement->y = 300 + knight->y_diff + 30;
    }
    else if (dx == 1 && dy == -1) // NE
    {
        graphics->source_rect.x = 0;
        graphics->source_rect.y = 0;
        graphics->source_rect.w = 29;
        graphics->source_rect.h = 29;

        movement->w = 60;
        movement->h = 60;

        movement->x = 365 + knight->x_diff + 30;
        movement->y = 300 + knight->y_diff - 30;
    }
    else if (dx == 1 && dy == 1) // SE
    {
        graphics->source_rect.x = 58;
        graphics->source_rect.y = 0;
        graphics->source_rect.w = 29;
        graphics->source_rect.h = 29;

        movement->w = 60;
        movement->h = 60;

        movement->x = 365 + knight->x_diff + 30;
        movement->y = 300 + knight->y_diff + 30;
    }
}


bool KnightSkillQ::IsCollide(int x0, int y0, int x1, int y1)
{
    Point<int> rect_s(x0, y0), rect_e(x1, y1);
    Point<int> s, e, s1, e1;
    int dx = movement->velocity_x, dy = movement->velocity_y;
    int curx = movement->x, cury = movement->y;
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
void KnightSkillQ::UpdateHitMonster()
{
    for (MonsterSke*& e : monster_genera->skeleton_list)
        if (e->IsMovingZone())
        {
            int x0 = e->movement->x + 20;
            int y0 = e->movement->y;
            int x1 = x0 + 40;
            int y1 = y0 + 30;
            if (IsCollide(x0, y0, x1, y1))
            {
                e->DecreseHealth(2 * knight->attack);
            }
        }
    for (MonsterBat*& e : monster_genera->bat_list)
        if (e->IsMovingZone())
        {
            int x0 = e->movement->x + 14;
            int y0 = e->movement->y + 5;
            int x1 = x0 + 25;
            int y1 = y0 + 20;
            if (IsCollide(x0, y0, x1, y1))
            {
                e->DecreaseHealth(2 * knight->attack);
            }
        }
    if (boss->IsActiveZone())
    {
        int x0 = boss->movement->x + 20;
        int y0 = boss->movement->y;
        int x1 = x0 + 60;
        int y1 = y0 + 90;
        if (IsCollide(x0, y0, x1, y1))
        {
            boss->DecreaseHealth(knight->attack);
        }
    }
}