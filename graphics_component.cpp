#include "graphics_component.h"
GraphicsComponent::GraphicsComponent() {}
GraphicsComponent::GraphicsComponent(const char* texture_file, MovementComponent* _movement, bool _animated)
{
    SetTexture(texture_file);
    movement = _movement;
    animated = _animated;
    Init();
}

GraphicsComponent::~GraphicsComponent()
{
    SDL_DestroyTexture(texture);
}

void GraphicsComponent::SetTexture(const char* texture_file)
{
    texture = TextureManager::LoadTexture(texture_file);
}

void GraphicsComponent::Init()
{
    source_rect.x = source_rect.y = 0;
    source_rect.w = source_rect.h = -1;
    destina_rect.h = movement->h;
    destina_rect.w = movement->w;
}

void GraphicsComponent::Update()
{
    if (animated)
    {
        source_rect.x = animation_width * static_cast<int> ((SDL_GetTicks() / speed) % frames);
        source_rect.y = animation_index;
        source_rect.w = animation_width;
        source_rect.h = animation_height;
    }
    
    destina_rect.x = static_cast<int> (movement->x);
    destina_rect.y = static_cast<int> (movement->y);
    destina_rect.h = movement->h;
    destina_rect.w = movement->w;
}
void GraphicsComponent::Draw()
{
    if (source_rect.w > 0)
        TextureManager::Draw(texture, source_rect, destina_rect);
    else
        TextureManager::Draw(texture, destina_rect);
}
void GraphicsComponent::Draw(int deltax, int deltay)
{
    destina_rect.x += deltax;
    destina_rect.y += deltay;
    if (source_rect.w > 0)
        TextureManager::Draw(texture, source_rect, destina_rect);
    else
        TextureManager::Draw(texture, destina_rect);
}

void GraphicsComponent::UseAnimation(const std::string& animationation_name)
{
    // 'animationation_name' in 'animationations_map'
    animation_index = anima_Map[animationation_name].index_row;
    animation_width = anima_Map[animationation_name].width;
    animation_height = anima_Map[animationation_name].height;
    frames = anima_Map[animationation_name].frames;
    speed = anima_Map[animationation_name].speed;
}