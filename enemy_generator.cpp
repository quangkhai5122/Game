#include "enemy_generator.h"
#include "world_map.h"
#include "player_manager.h"
#include <algorithm>
EnemyGenerator::EnemyGenerator()
{
    generator_interval = 200;
}
EnemyGenerator::~EnemyGenerator()
{
    for (EnemyBat*& e : bat_container)
        delete e;
    for (EnemySkeleton*& e : skeleton_container)
        delete e;
}

void EnemyGenerator::AddNewSkeleton(int x, int y)
{
    EnemySkeleton* enemy = new EnemySkeleton(x, y);
    skeleton_container.push_back(enemy);
}
void EnemyGenerator::AddNewBat(int x, int y)
{
    EnemyBat* enemy = new EnemyBat(x, y);
    bat_container.push_back(enemy);
}
void EnemyGenerator::Update()
{

    if (skeleton_container.size() < MAX_ENEMY)
    {
        if (--generator_interval == 0) 
        {
            generator_interval = 200;
            int x_left = -((player->xdif % 32 + 32) % 32);
            int y_left = -((player->ydif % 32 + 32) % 32);
            int X_tile = (player->xdif / 32) + ((x_left != 0 && player->xdif < 0) ? -1 : 0);
            int Y_tile = (player->ydif / 32) + ((y_left != 0 && player->ydif < 0) ? -1 : 0);

            std::vector<std::pair<int, int> > grass;
            
            for (int x = x_left - 160, x_tile = X_tile - 5; x < 928; x += 32, x_tile++)
                for (int y = y_left - 160, y_tile = Y_tile - 5; y < 768; y += 32, y_tile++)
                    if (x < x_left - 32 || x >= 832 || y < y_left - 32 || y >= 672)
                    {
                        int tile0 = map->GetTileType(x_tile, y_tile);
                        int tile1 = map->GetTileType(x_tile - 1, y_tile);
                        int tile2 = map->GetTileType(x_tile, y_tile - 1);
                        int tile3 = map->GetTileType(x_tile - 1, y_tile - 1);
                        if (map->InsideGrassZone(x, y))
                            tile0 = 2; // set to grass
                        if (map->InsideGrassZone(x - 32, y))
                            tile1 = 2; // set to grass
                        if (map->InsideGrassZone(x, y - 32))
                            tile2 = 2; // set to grass
                        if (map->InsideGrassZone(x - 32, y - 32))
                            tile3 = 2; // set to grass
                        int mx = std::max({ tile0, tile1, tile2, tile3 });
                        int mn = std::min({ tile0, tile1, tile2, tile3 });
                        if (2 <= mn && mx <= 4)
                            grass.push_back({ x - 20, y - 15 });
                    }
            if (!grass.empty())
            {
                int index = rand() % ((int)grass.size());
                AddNewSkeleton(grass[index].first + player->xdif, grass[index].second + player->ydif);
                index = rand() % ((int)grass.size());
                AddNewBat(grass[index].first + player->xdif, grass[index].second + player->ydif);
            }

        }
    }

    std::vector<EnemySkeleton*> tmp;
    for (EnemySkeleton*& e : skeleton_container)
    {
        if (e->IsAlive() && e->IsInsideLivingZone())
        {
            e->Update();
            tmp.push_back(e);
        }
        else
            delete e;
    }
    skeleton_container = std::move(tmp);


    std::vector<EnemyBat*> tmp1;
    for (EnemyBat*& e : bat_container)
    {
        if (e->IsAlive() && e->IsInsideLivingZone())
        {
            e->Update();
            tmp1.push_back(e);
        }
        else
            delete e;
    }
    bat_container = std::move(tmp1);
}
void EnemyGenerator::Render()
{
    for (EnemySkeleton*& e : skeleton_container)
        e->Render();
    for (EnemyBat*& e : bat_container)
        e->Render();
}