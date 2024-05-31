#include "bullet_list.h"
#include "pointOxy.h"
#include "knight_manager.h"
Bullet::Bullet(int x, int y, bool advanced)
{
    if (advanced)
    {
        movement = new MovementComponent(x, y, 6, 20, 20);
        graphics = new GraphicsComponent("img/gamemenu/shooting_ball_1.png", movement, false); // boss

        damages = 20;
        isactives = true;
        timeduration = 100;
    }
    else
    {
        movement = new MovementComponent(x, y, 3.5, 20, 20);
        graphics = new GraphicsComponent("img/gamemenu/shooting_ball.png", movement, false); // bats

        damages = 10;
        isactives = true;
        timeduration = 150;
    }
    
    int screenX = x - knight->x_diff, screenY = y - knight->y_diff;
    Point<double> vec(400 - screenX, 320 - screenY);
    double dist = vec.dist();
    if (dist < 0.5) dist = 0.5;
    vec = vec / dist;

    movement->SetDir(vec.x, vec.y);
}
Bullet::~Bullet()
{
    delete movement;
    delete graphics;
}
void Bullet::Updated()
{
    if (isactives == false)
        return;
    movement->Update();
    graphics->Update();

    if (CollidesKnight())
    {
        knight->DecreaseHealth(damages);
        isactives = false;
    }
    if (--timeduration == 0)
        isactives = false;
}
void Bullet::Rendered()
{
    graphics->Draw(-knight->x_diff, -knight->y_diff);
}

bool Bullet::IsActives()
{
    return isactives;
}

bool Bullet::CollidesKnight()
{
    int x = movement->x - knight->x_diff;
    int y = movement->y - knight->y_diff;
    return std::max(x, 390) <= std::min(x + 20, 410)
        && std::max(y, 308) <= std::min(y + 20, 332);
}