#pragma once 

#include "texture_manager.h"
#include <random>
#include <array>
#include "perlin_noise.h"


class WorldMap
{
public:
    WorldMap();
    ~WorldMap();

    int GetTileType(int x, int y);
    void UpdateMap();
    void RenderMap();
    void RenderMapFullGrass();
    bool IsValidMove(const std::pair<int, int>& dir);

    bool InsideGrassZone(int x, int y);
    PerlinNoise* perlin_noise;
private:

    SDL_Rect tmp_src{ 0, 0, 0, 0 };  
    SDL_Rect tmp_dest{ 0, 0, 0, 0 }; 
    std::array<SDL_Texture*, 6> tile_type;


    
    std::vector<std::array<int, 3>> tiles_near_player;
};

extern WorldMap* map;