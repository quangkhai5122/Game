#include "movement_component.h"

MovementComponent::MovementComponent(int _x, int _y, double _speed, int _w, int _h)
{
    x = _x;
    y = _y;
    speed = _speed;

    // Doesn't move
    velocity_x = velocity_y = 0;

    h = _h;
    w = _w;
}

MovementComponent::~MovementComponent() {}

void MovementComponent::Update()
{
    x += speed * velocity_x;
    y += speed * velocity_y;
}
void MovementComponent::SetDir(double _vx, double _vy)
{
    velocity_x = _vx;
    velocity_y = _vy;
}
void MovementComponent::SetPosition(int _x, int _y)
{
    x = _x;
    y = _y;
}
void MovementComponent::SetSpeed(double _speed)
{
    speed = _speed;
}
void MovementComponent::AddSpeed(double v)
{
    speed += v;
}