#include "shooter.h"
#include "sound_manager.h"
Shooter::Shooter() {}
Shooter::~Shooter()
{
    for (Bullet*& b : bullet_container)
        delete b;

}
void Shooter::AddNewBullet(int x, int y, bool advanced)
{
    Bullet* bullet = new Bullet(x, y, advanced);
    bullet_container.push_back(bullet);
    sound_manager->PlayShoot();
}
void Shooter::Update()
{
    std::vector<Bullet*> tmp;
    for (Bullet*& b : bullet_container)
    {
        b->Update();
        if (b->IsActive())
            tmp.push_back(b);
        else
            delete b;
    }
    bullet_container = std::move(tmp);
}
void Shooter::Render()
{
    for (Bullet*& b : bullet_container)
        b->Render();
}