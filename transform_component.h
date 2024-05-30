#pragma once

class TransformComponent
{
public:
    double x, y;
    double speed;

    // Velocity (Direction) of x and y
    double vx, vy;

    int h, w;
    TransformComponent(int _x, int _y, double _speed, int _w, int _h);
    ~TransformComponent();
    void Update();
    void SetDir(double _vx, double _vy);
    void SetPosition(int _x, int _y);
    void SetSpeed(double _speed);
    void AddSpeed(double v);
};