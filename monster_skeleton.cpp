#include "monster_skeleton.h"
#include "knight_manager.h"
#include "map.h"
#include "mixsound_manager.h"
MonsterSke::MonsterSke(int x, int y)
{
    movement = new MovementComponent(x, y, 1, 70, 40);
    graphics = new GraphicsComponent("img/monster/enemy_skeleton.png", movement, true);
    blood = 60;
    blood_bar = new MonsterHealthBar(movement, 25, 5, blood);
    exp = 1;
    attacks = 1;
    attack_intervals = 3;
    attack_r = 200;
    move_durative = 50;
    Dx = Dy = 0;
    AddAnimations();
    graphics->UseAnimation("idle_right");
    direct = 1;
    sound_manager->PlayMonsterAppear();
}
MonsterSke::~MonsterSke()
{
    delete movement;
    delete graphics;
    delete blood_bar;
}

void MonsterSke::AddAnimations()
{
    Animation walk_right(0, 31, 17, 4, 200);
    Animation walk_left(17, 31, 17, 4, 200);
    Animation sword_right(34, 31, 17, 4, 150);
    Animation sword_left(51, 31, 17, 4, 150);
    graphics->anima_Map["idle_right"] = walk_right;
    graphics->anima_Map["idle_left"] = walk_left;
    graphics->anima_Map["walk_right"] = walk_right;
    graphics->anima_Map["walk_left"] = walk_left;
    graphics->anima_Map["sword_right"] = sword_right;
    graphics->anima_Map["sword_left"] = sword_left;
}
void MonsterSke::Updated()
{
    
    if (IsMovingZone())
    {
        if (IsNextsToKnight()) 
        {
            if (movement->x - knight->x_diff <= 380)
                graphics->UseAnimation("sword_right");
            else
                graphics->UseAnimation("sword_left");
            if (graphics->source_rect.x == 3 * 31)
            {
                if (--attack_intervals == 0)
                {
                    attack_intervals = 3;
                    knight->DecreaseHealth(attacks);
                }

            }
        }
        else
        {
            if (--move_durative == 0)
            {
                if (IsNearsKnight())
                {
                    move_durative = 1;
                    movement->speed = 2;
                    if (movement->x - knight->x_diff + 15 < 380)
                        Dx = 1;
                    else if (movement->x - knight->x_diff + 10 > 380)
                        Dx = -1;
                    else Dx = 0;
                    if (movement->y - knight->y_diff + 10 < 300)
                        Dy = 1;
                    else if (movement->y - knight->y_diff + 5 > 300)
                        Dy = -1;
                    else Dy = 0;
                }
                else
                {
                    move_durative = 50;
                    movement->speed = 1;
                    Dx = (rand() % 3) - 1; // [-1, 0, 1]
                    Dy = (rand() % 3) - 1; // [-1, 0, 1]
                }
                if (Dx == 1)
                {
                    graphics->UseAnimation("walk_right");
                    direct = 1;
                }
                else if (Dx == -1)
                {
                    graphics->UseAnimation("walk_left");
                    direct = 0;
                }
            }
            else if (move_durative == 10)
                Dx = Dy = 0;


            if (move_durative & 1)
            {
                if (CheckMoveCollidion())
                {
                    movement->x += Dx * movement->speed;
                    movement->y += Dy * movement->speed;
                }
            }
        }

    }

    graphics->Update();
    blood_bar->Update(23, -7);
}
void MonsterSke::Render()
{
    graphics->Draw(-knight->x_diff, -knight->y_diff);
    blood_bar->Draw(-knight->x_diff, -knight->y_diff);
}

bool MonsterSke::IsLivingZone()
{
    int x = movement->x - knight->x_diff;
    int y = movement->y - knight->y_diff;
    return (-1000 < x && x < 2000 && -1000 < y && y < 2000);
}
bool MonsterSke::IsMovingZone()
{
    int x = movement->x - knight->x_diff;
    int y = movement->y - knight->y_diff;
    return (-160 < x && x < 928 && -160 < y && y < 768);
}


bool MonsterSke::CheckMoveCollidion()
{
    
    if (Dx == 0 && Dy == 0)
        return 1;

    
    int curx = movement->x - knight->x_diff + Dx * movement->speed;
    int cury = movement->y - knight->y_diff + Dy * movement->speed;

    
    bool valid_move = 1;
    int x_l = -((knight->x_diff % 32 + 32) % 32);
    int y_l = -((knight->y_diff % 32 + 32) % 32);
    int X_ti = (knight->x_diff / 32) + ((x_l != 0 && knight->x_diff < 0) ? -1 : 0);
    int Y_ti = (knight->y_diff / 32) + ((y_l != 0 && knight->y_diff < 0) ? -1 : 0);

    while (x_l + 32 <= curx - 96) x_l += 32, X_ti++;
    while (x_l > curx - 96) x_l -= 32, X_ti--;
    while (y_l + 32 <= cury - 96) y_l += 32, Y_ti++;
    while (y_l > cury - 96) y_l -= 32, Y_ti--;
    for (int x = x_l, X_ti = X_ti; X_ti < X_ti + 8; x += 32, X_ti++)
        for (int y = y_l, Y_ti = Y_ti; Y_ti < Y_ti + 8; y += 32, Y_ti++)
        {
            int tile = map->GetTilekind(X_ti, Y_ti);
            if (map->GrassZone(x, y))
                continue; // tile = 2; // set to grass
            int sz = (tile == 5 ? 64 : 32);
            int x0 = x + (sz == 64 ? 4 : 0);
            int y0 = y + (sz == 64 ? 4 : 0);
            int x1 = x + sz - (sz == 64 ? 4 : 0);
            int y1 = y + sz - (sz == 64 ? 25 : 15);
            if ((tile <= 1 || tile == 5) && TileCollidionEnemy(x0, y0, x1, y1, curx, cury))
            {
                valid_move = false;
                goto Next;
            }

        }
    if (knight->CollideWithKnight(curx + 20, cury + 6, curx + 50, cury + 26))
        valid_move = false;
Next:;
    return valid_move;
}

bool MonsterSke::TileCollidionEnemy(int x0, int y0, int x1, int y1, int X, int Y)
{
    return (std::max(x0, X + 22) <= std::min(x1, X + 43))
        && (std::max(y0, Y - 2) <= std::min(y1, Y + 40));
}

bool MonsterSke::IsAlives()
{
    return blood > 0;
}

bool MonsterSke::IsNearsKnight()
{
    int X = movement->x - knight->x_diff - 365;
    int Y = movement->y - knight->y_diff - 300;
    return  X * X + Y * Y <= attack_r * attack_r;
}

bool MonsterSke::IsNextsToKnight()
{
    int curx = movement->x - knight->x_diff;
    int cury = movement->y - knight->y_diff;
    return knight->CollideWithKnight(curx + 17, cury + 6, curx + 53, cury + 26);
}

void MonsterSke::DecreseHealth(int v)
{
    blood -= v;
    blood_bar->Reset(blood);
    if (blood <= 0)
        knight->exp += exp;
}