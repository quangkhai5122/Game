#include "knight_skill_e.h"
#include "knight_manager.h"
#include "monster_generator.h"
#include "pointOxy.h"
#include "mixsound_manager.h"
KnightSkillE::KnightSkillE()
{
    cldown = 0;
    cldown_base = 300;
    durative = 0;
    durative_base = 700;

    circ_on = TextureManager::LoadTexture("img/knight/e_circon.png");
    circ_off = TextureManager::LoadTexture("img/knight/e_circoff.png");
    circ.x = 680, circ.y = 450;
    circ.w = circ.h = 80;

    movement = new MovementComponent(348, 275, 0, 100, 100);
    graphics = new GraphicsComponent("img/knight/e_anima.png", movement, false);

}

KnightSkillE::~KnightSkillE()
{
    delete movement;
    delete graphics;
    SDL_DestroyTexture(circ_on);
    SDL_DestroyTexture(circ_off);
}

void KnightSkillE::Updated()
{
    if (durative > 0)
    {
        graphics->Update();
        durative--;
        if (durative == 0)
        {
            // Hết thời gian hiệu lực, reset trạng thái miễn nhiễm
            knight->SetInvincible(false);
        }
    }
}
void KnightSkillE::Rendered()
{
    if (cldown == 0)
        TextureManager::Draw(circ_on, circ);
    else
    {
        cldown--;
        TextureManager::Draw(circ_off, circ);
    }
    if (durative > 0)
    {
        //durative--;
        graphics->Draw();
    }
}
void KnightSkillE::ExecuteSkill()
{
    // Kiểm tra nếu kỹ năng có thể được kích hoạt
    if (cldown == 0 || cldown >= 40)
    {
        if (knight->dir)
            knight->graphics->UseAnimation("sword_right");
        else
            knight->graphics->UseAnimation("sword_left");
    }

    // Nếu kỹ năng đang trong thời gian hồi chiêu, thoát khỏi hàm
    if (cldown > 0)
        return;

    sound_manager->PlayE();

    // Đặt thời gian hiệu lực của kỹ năng
    durative = durative_base;

    // Đặt thời gian hồi chiêu của kỹ năng
    cldown = cldown_base;

    // Kích hoạt trạng thái miễn nhiễm sát thương
    knight->SetInvincible(true);
}
