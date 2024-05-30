#include "enemy_skeleton.h"
#include "player_manager.h"
#include "world_map.h"
#include "sound_manager.h"
EnemySkeleton::EnemySkeleton(int x, int y)
{
    transform = new TransformComponent(x, y, 1, 70, 40);
    sprite = new SpriteComponent("img/enemy/enemy_skeleton.png", transform, true);
    health = 60;
    health_bar = new EnemyHealthBar(transform, 25, 5, health);
    xp = 1;
    attack = 1;
    attack_interval = 3;
    attack_radius = 200;
    move_duration = 50;
    dx = dy = 0;
    AddAnimations();
    sprite->ApplyAnimation("idle_right");
    direction = 1;
    sound_manager->PlayMonsterAppear();
}
EnemySkeleton::~EnemySkeleton()
{
    delete transform;
    delete sprite;
    delete health_bar;
}

void EnemySkeleton::AddAnimations()
{
    Animation walk_right(0, 31, 17, 4, 200);
    Animation walk_left(17, 31, 17, 4, 200);
    Animation sword_right(34, 31, 17, 4, 150);
    Animation sword_left(51, 31, 17, 4, 150);
    sprite->animations_map["idle_right"] = walk_right;
    sprite->animations_map["idle_left"] = walk_left;
    sprite->animations_map["walk_right"] = walk_right;
    sprite->animations_map["walk_left"] = walk_left;
    sprite->animations_map["sword_right"] = sword_right;
    sprite->animations_map["sword_left"] = sword_left;
}
void EnemySkeleton::Update()
{
    
    if (IsInsideMovingZone())
    {
        if (IsNextToPlayer()) 
        {
            if (transform->x - player->xdif <= 380)
                sprite->ApplyAnimation("sword_right");
            else
                sprite->ApplyAnimation("sword_left");
            if (sprite->src_rect.x == 3 * 31)
            {
                if (--attack_interval == 0)
                {
                    attack_interval = 3;
                    player->DecHealth(attack);
                }

            }
        }
        else
        {
            if (--move_duration == 0)
            {
                if (IsNearPlayer())
                {
                    move_duration = 1;
                    transform->speed = 2;
                    if (transform->x - player->xdif + 15 < 380)
                        dx = 1;
                    else if (transform->x - player->xdif + 10 > 380)
                        dx = -1;
                    else dx = 0;
                    if (transform->y - player->ydif + 10 < 300)
                        dy = 1;
                    else if (transform->y - player->ydif + 5 > 300)
                        dy = -1;
                    else dy = 0;
                }
                else
                {
                    move_duration = 50;
                    transform->speed = 1;
                    dx = (rand() % 3) - 1; // [-1, 0, 1]
                    dy = (rand() % 3) - 1; // [-1, 0, 1]
                }
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
                if (CheckMoveCollide())
                {
                    transform->x += dx * transform->speed;
                    transform->y += dy * transform->speed;
                }
            }
        }

    }

    sprite->Update();
    health_bar->Update(23, -7);
}
void EnemySkeleton::Render()
{
    sprite->Draw(-player->xdif, -player->ydif);
    health_bar->Draw(-player->xdif, -player->ydif);
}

bool EnemySkeleton::IsInsideLivingZone()
{
    int x = transform->x - player->xdif;
    int y = transform->y - player->ydif;
    return (-1000 < x && x < 2000 && -1000 < y && y < 2000);
}
bool EnemySkeleton::IsInsideMovingZone()
{
    int x = transform->x - player->xdif;
    int y = transform->y - player->ydif;
    return (-160 < x && x < 928 && -160 < y && y < 768);
}

/**
 *  @brief Try moving and check if it'll collide with anything.
           Only check if enemy is inside moving zone, i.e., IsInsideMovingZone(...) is true.
 *  @return 1 if enemy moves and it collides with deep_water, water, tree; 0 otherwise.
 */
bool EnemySkeleton::CheckMoveCollide()
{
    // If don't move, return 1
    if (dx == 0 && dy == 0)
        return 1;

    // Try moving
    int curx = transform->x - player->xdif + dx * transform->speed;
    int cury = transform->y - player->ydif + dy * transform->speed;

    // Iterate the surrounding tiles and check for collision
    bool valid_move = 1;
    int x_left = -((player->xdif % 32 + 32) % 32);
    int y_left = -((player->ydif % 32 + 32) % 32);
    int X_tile = (player->xdif / 32) + ((x_left != 0 && player->xdif < 0) ? -1 : 0);
    int Y_tile = (player->ydif / 32) + ((y_left != 0 && player->ydif < 0) ? -1 : 0);

    while (x_left + 32 <= curx - 96) x_left += 32, X_tile++;
    while (x_left > curx - 96) x_left -= 32, X_tile--;
    while (y_left + 32 <= cury - 96) y_left += 32, Y_tile++;
    while (y_left > cury - 96) y_left -= 32, Y_tile--;
    for (int x = x_left, x_tile = X_tile; x_tile < X_tile + 8; x += 32, x_tile++)
        for (int y = y_left, y_tile = Y_tile; y_tile < Y_tile + 8; y += 32, y_tile++)
        {
            int tile = map->GetTileType(x_tile, y_tile);
            if (map->InsideGrassZone(x, y))
                continue; // tile = 2; // set to grass
            int sz = (tile == 5 ? 64 : 32);
            int x0 = x + (sz == 64 ? 4 : 0);
            int y0 = y + (sz == 64 ? 4 : 0);
            int x1 = x + sz - (sz == 64 ? 4 : 0);
            int y1 = y + sz - (sz == 64 ? 25 : 15);
            if ((tile <= 1 || tile == 5) && TileCollideEnemy(x0, y0, x1, y1, curx, cury))
            {
                valid_move = false;
                goto Next;
            }

        }
    if (player->CollidePlayer(curx + 20, cury + 6, curx + 50, cury + 26))
        valid_move = false;
Next:;
    return valid_move;
}

bool EnemySkeleton::TileCollideEnemy(int x0, int y0, int x1, int y1, int X, int Y)
{
    return (std::max(x0, X + 22) <= std::min(x1, X + 43))
        && (std::max(y0, Y - 2) <= std::min(y1, Y + 40));
}

bool EnemySkeleton::IsAlive()
{
    return health > 0;
}

bool EnemySkeleton::IsNearPlayer()
{
    int X = transform->x - player->xdif - 365;
    int Y = transform->y - player->ydif - 300;
    return  X * X + Y * Y <= attack_radius * attack_radius;
}

bool EnemySkeleton::IsNextToPlayer()
{
    int curx = transform->x - player->xdif;
    int cury = transform->y - player->ydif;
    return player->CollidePlayer(curx + 17, cury + 6, curx + 53, cury + 26);
}

void EnemySkeleton::DecHealth(int v)
{
    health -= v;
    health_bar->Reset(health);
    if (health <= 0)
        player->xp += xp;
}