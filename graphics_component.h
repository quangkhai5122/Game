#pragma once
#include "texturer_manager.h"
#include "movement_component.h"
#include "anima.h"
#include <map>
#include <string>
#include <SDL.h>
class GraphicsComponent
{
private:

    SDL_Texture* texture;
    MovementComponent* movement;

public:
    SDL_Rect source_rect, destina_rect;
    bool animated = false;
    int frames = 1;
    int speed = 100;
    int animation_index = 0;
    int animation_width = 0;
    int animation_height = 0;
    // Add animations to the map manually
    std::map<std::string, Animation> anima_Map;

    GraphicsComponent();
    GraphicsComponent(const char* texture_file, MovementComponent* _movement, bool _animated);
    ~GraphicsComponent();
    void SetTexture(const char* texture_file);
    void Init();
    void Update();
    void Draw();
    void Draw(int deltax, int deltay);
    void UseAnimation(const std::string& animation);
};


