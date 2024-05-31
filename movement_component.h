#pragma once

class MovementComponent
{
public:
    double x, y;
    double speed;

    // Velocity (Direction) of x and y
    double velocity_x, velocity_y;

    int h, w;
    MovementComponent(int _x, int _y, double _speed, int _w, int _h);
    ~MovementComponent();
    void Update();
    void SetDir(double _vx, double _vy);
    void SetPosition(int _x, int _y);
    void SetSpeed(double _speed);
    void AddSpeed(double v);
};