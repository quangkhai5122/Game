#include "bullet.h"
#include "point_2d.h"
#include "player_manager.h"
Bullet::Bullet(int x, int y, bool advanced)
{
    if (advanced)
    {
        transform = new TransformComponent(x, y, 6, 20, 20);
        sprite = new SpriteComponent("img/game/shooting_ball_1.png", transform, false); // boss

        damage = 20;
        active = true;
        duration = 100;
    }
    else
    {
        transform = new TransformComponent(x, y, 3.5, 20, 20);
        sprite = new SpriteComponent("img/game/shooting_ball.png", transform, false); // bats

        damage = 10;
        active = true;
        duration = 150;
    }
    
    int screenX = x - player->xdif, screenY = y - player->ydif;
    Point<double> vec(400 - screenX, 320 - screenY);
    double dist = vec.dist();
    if (dist < 0.5) dist = 0.5;
    vec = vec / dist;

    transform->SetDir(vec.x, vec.y);
}
Bullet::~Bullet()
{
    delete transform;
    delete sprite;
}
void Bullet::Update()
{
    if (active == false)
        return;
    transform->Update();
    sprite->Update();

    if (CollidePlayer())
    {
        player->DecHealth(damage);
        active = false;
    }
    if (--duration == 0)
        active = false;
}
void Bullet::Render()
{
    sprite->Draw(-player->xdif, -player->ydif);
}

bool Bullet::IsActive()
{
    return active;
}

bool Bullet::CollidePlayer()
{
    int x0 = transform->x - player->xdif;
    int y0 = transform->y - player->ydif;
    return std::max(x0, 390) <= std::min(x0 + 20, 410)
        && std::max(y0, 308) <= std::min(y0 + 20, 332);
}