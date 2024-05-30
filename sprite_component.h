#pragma once
#include "texture_manager.h"
#include "transform_component.h"
#include "animation.h"
#include <map>
#include <string>
#include <SDL.h>
class SpriteComponent
{
private:

    SDL_Texture* texture;
    TransformComponent* transform;

public:
    SDL_Rect src_rect, dest_rect;
    bool animated = false;
    int frames = 1;
    int speed = 100;
    int anim_index = 0;
    int anim_width = 0;
    int anim_height = 0;
    // Add animations to the map manually
    std::map<std::string, Animation> animations_map;

    SpriteComponent();
    SpriteComponent(const char* texture_file, TransformComponent* _transform, bool _animated);
    ~SpriteComponent();
    void SetTexture(const char* texture_file);
    void Init();
    void Update();
    void Draw();
    void Draw(int deltax, int deltay);
    void ApplyAnimation(const std::string& animation);
};


