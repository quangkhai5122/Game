#include "player_skill_e.h"
#include "player_manager.h"
#include "enemy_generator.h"
#include "point_2d.h"
#include "sound_manager.h"
PlayerSkillE::PlayerSkillE()
{
    cooldown = 0;
    cooldown_base = 300;
    duration = 0;
    duration_base = 700;

    circle_on = TextureManager::LoadTexture("img/player/e_circle_on.png");
    circle_off = TextureManager::LoadTexture("img/player/e_circle_off.png");
    circle.x = 680, circle.y = 450;
    circle.w = circle.h = 80;

    transform = new TransformComponent(348, 275, 0, 100, 100);
    sprite = new SpriteComponent("img/player/e_animation.png", transform, false);

}

PlayerSkillE::~PlayerSkillE()
{
    delete transform;
    delete sprite;
    SDL_DestroyTexture(circle_on);
    SDL_DestroyTexture(circle_off);
}

void PlayerSkillE::Update()
{
    if (duration > 0)
    {
        sprite->Update();
        duration--;
        if (duration == 0)
        {
            // Hết thời gian hiệu lực, reset trạng thái miễn nhiễm
            player->SetInvincible(false);
        }
    }
}
void PlayerSkillE::Render()
{
    if (cooldown == 0)
        TextureManager::Draw(circle_on, circle);
    else
    {
        cooldown--;
        TextureManager::Draw(circle_off, circle);
    }
    if (duration > 0)
    {
        //duration--;
        sprite->Draw();
    }
}
void PlayerSkillE::ExecuteSkill()
{
    // Kiểm tra nếu kỹ năng có thể được kích hoạt
    if (cooldown == 0 || cooldown >= 40)
    {
        if (player->direction)
            player->sprite->ApplyAnimation("sword_right");
        else
            player->sprite->ApplyAnimation("sword_left");
    }

    // Nếu kỹ năng đang trong thời gian hồi chiêu, thoát khỏi hàm
    if (cooldown > 0)
        return;

    sound_manager->PlayE();

    // Đặt thời gian hiệu lực của kỹ năng
    duration = duration_base;

    // Đặt thời gian hồi chiêu của kỹ năng
    cooldown = cooldown_base;

    // Kích hoạt trạng thái miễn nhiễm sát thương
    player->SetInvincible(true);
}
