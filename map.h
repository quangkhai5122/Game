#pragma once 

#include "texturer_manager.h"
#include <random>
#include <array>
#include "perli_noise.h"


class WorldMap
{
public:
    WorldMap();
    ~WorldMap();

    int GetTilekind(int x, int y);
    void Update();
    void Render();
    void MapGrass();
    bool IsMove(const std::pair<int, int>& dir);

    bool GrassZone(int x, int y);
    PerlinNoise* perlin_noise;
private:

    SDL_Rect tmp_src{ 0, 0, 0, 0 };  
    SDL_Rect tmp_dest{ 0, 0, 0, 0 }; 
    std::array<SDL_Texture*, 6> tile_kind;


    
    std::vector<std::array<int, 3>> near_knight;
};

extern WorldMap* map;