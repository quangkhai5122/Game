#pragma once
#include <vector>
#include "bullet_list.h"
class Shoot
{
public:
    Shoot();
    ~Shoot();
    void AddNewBullets(int x, int y, bool advanced);
    void Updated();
    void Rendered();
    std::vector<Bullet*> bullet_list;
private:
};

extern Shoot* shoot;