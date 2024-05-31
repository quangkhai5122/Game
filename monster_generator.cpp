#include "monster_generator.h"
#include "map.h"
#include "knight_manager.h"
#include <algorithm>
MonsterGenerate::MonsterGenerate()
{
    generate_intervals = 200;
}
MonsterGenerate::~MonsterGenerate()
{
    for (MonsterBat*& e : bat_list)
        delete e;
    for (MonsterSke*& e : skeleton_list)
        delete e;
}

void MonsterGenerate::AddNewSke(int x, int y)
{
    MonsterSke* Monster = new MonsterSke(x, y);
    skeleton_list.push_back(Monster);
}
void MonsterGenerate::AddNewBatman(int x, int y)
{
    MonsterBat* Monster = new MonsterBat(x, y);
    bat_list.push_back(Monster);
}
void MonsterGenerate::Updated()
{

    if (skeleton_list.size() < MAX_MONSTER)
    {
        if (--generate_intervals == 0) 
        {
            generate_intervals = 200;
            int x_left = -((knight->x_diff % 32 + 32) % 32);
            int y_left = -((knight->y_diff % 32 + 32) % 32);
            int X_tile = (knight->x_diff / 32) + ((x_left != 0 && knight->x_diff < 0) ? -1 : 0);
            int Y_tile = (knight->y_diff / 32) + ((y_left != 0 && knight->y_diff < 0) ? -1 : 0);

            std::vector<std::pair<int, int> > grass;
            
            for (int x = x_left - 160, x_tile = X_tile - 5; x < 928; x += 32, x_tile++)
                for (int y = y_left - 160, y_tile = Y_tile - 5; y < 768; y += 32, y_tile++)
                    if (x < x_left - 32 || x >= 832 || y < y_left - 32 || y >= 672)
                    {
                        int tile0 = map->GetTilekind(x_tile, y_tile);
                        int tile1 = map->GetTilekind(x_tile - 1, y_tile);
                        int tile2 = map->GetTilekind(x_tile, y_tile - 1);
                        int tile3 = map->GetTilekind(x_tile - 1, y_tile - 1);
                        if (map->GrassZone(x, y))
                            tile0 = 2; // set to grass
                        if (map->GrassZone(x - 32, y))
                            tile1 = 2; // set to grass
                        if (map->GrassZone(x, y - 32))
                            tile2 = 2; // set to grass
                        if (map->GrassZone(x - 32, y - 32))
                            tile3 = 2; // set to grass
                        int mx = std::max({ tile0, tile1, tile2, tile3 });
                        int mn = std::min({ tile0, tile1, tile2, tile3 });
                        if (2 <= mn && mx <= 4)
                            grass.push_back({ x - 20, y - 15 });
                    }
            if (!grass.empty())
            {
                int index = rand() % ((int)grass.size());
                AddNewSke(grass[index].first + knight->x_diff, grass[index].second + knight->y_diff);
                index = rand() % ((int)grass.size());
                AddNewBatman(grass[index].first + knight->x_diff, grass[index].second + knight->y_diff);
            }

        }
    }

    std::vector<MonsterSke*> tmp;
    for (MonsterSke*& e : skeleton_list)
    {
        if (e->IsAlives() && e->IsLivingZone())
        {
            e->Updated();
            tmp.push_back(e);
        }
        else
            delete e;
    }
    skeleton_list = std::move(tmp);


    std::vector<MonsterBat*> tmp1;
    for (MonsterBat*& e : bat_list)
    {
        if (e->IsAlives() && e->IsLivingZone())
        {
            e->Updated();
            tmp1.push_back(e);
        }
        else
            delete e;
    }
    bat_list = std::move(tmp1);
}
void MonsterGenerate::Rendered()
{
    for (MonsterSke*& e : skeleton_list)
        e->Render();
    for (MonsterBat*& e : bat_list)
        e->Rendered();
}