#include "Shoot.h"
#include "mixsound_manager.h"
Shoot::Shoot() {}
Shoot::~Shoot()
{
    for (Bullet*& b : bullet_list)
        delete b;

}
void Shoot::AddNewBullets(int x, int y, bool advanced)
{
    Bullet* bullet = new Bullet(x, y, advanced);
    bullet_list.push_back(bullet);
    sound_manager->PlayShoot();
}
void Shoot::Updated()
{
    std::vector<Bullet*> tmp;
    for (Bullet*& b : bullet_list)
    {
        b->Updated();
        if (b->IsActives())
            tmp.push_back(b);
        else
            delete b;
    }
    bullet_list = std::move(tmp);
}
void Shoot::Rendered()
{
    for (Bullet*& b : bullet_list)
        b->Rendered();
}