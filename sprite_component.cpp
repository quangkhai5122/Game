#include "sprite_component.h"
SpriteComponent::SpriteComponent() {}
SpriteComponent::SpriteComponent(const char* texture_file, TransformComponent* _transform, bool _animated)
{
    SetTexture(texture_file);
    transform = _transform;
    animated = _animated;
    Init();
}

SpriteComponent::~SpriteComponent()
{
    SDL_DestroyTexture(texture);
}

void SpriteComponent::SetTexture(const char* texture_file)
{
    texture = TextureManager::LoadTexture(texture_file);
}

void SpriteComponent::Init()
{
    src_rect.x = src_rect.y = 0;
    src_rect.w = src_rect.h = -1;
    dest_rect.h = transform->h;
    dest_rect.w = transform->w;
}

void SpriteComponent::Update()
{
    if (animated)
    {
        src_rect.x = anim_width * static_cast<int> ((SDL_GetTicks() / speed) % frames);
        src_rect.y = anim_index;
        src_rect.w = anim_width;
        src_rect.h = anim_height;
    }
    
    dest_rect.x = static_cast<int> (transform->x);
    dest_rect.y = static_cast<int> (transform->y);
    dest_rect.h = transform->h;
    dest_rect.w = transform->w;
}
void SpriteComponent::Draw()
{
    if (src_rect.w > 0)
        TextureManager::Draw(texture, src_rect, dest_rect);
    else
        TextureManager::Draw(texture, dest_rect);
}
void SpriteComponent::Draw(int deltax, int deltay)
{
    dest_rect.x += deltax;
    dest_rect.y += deltay;
    if (src_rect.w > 0)
        TextureManager::Draw(texture, src_rect, dest_rect);
    else
        TextureManager::Draw(texture, dest_rect);
}

void SpriteComponent::ApplyAnimation(const std::string& animation_name)
{
    // 'animation_name' in 'animations_map'
    anim_index = animations_map[animation_name].index_row;
    anim_width = animations_map[animation_name].width;
    anim_height = animations_map[animation_name].height;
    frames = animations_map[animation_name].frames;
    speed = animations_map[animation_name].speed;
}