#include "transform_component.h"

TransformComponent::TransformComponent(int _x, int _y, double _speed, int _w, int _h)
{
    x = _x;
    y = _y;
    speed = _speed;

    // Doesn't move
    vx = vy = 0;

    h = _h;
    w = _w;
}

TransformComponent::~TransformComponent() {}

void TransformComponent::Update()
{
    x += speed * vx;
    y += speed * vy;
}
void TransformComponent::SetDir(double _vx, double _vy)
{
    vx = _vx;
    vy = _vy;
}
void TransformComponent::SetPosition(int _x, int _y)
{
    x = _x;
    y = _y;
}
void TransformComponent::SetSpeed(double _speed)
{
    speed = _speed;
}
void TransformComponent::AddSpeed(double v)
{
    speed += v;
}