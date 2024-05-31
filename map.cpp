#include "map.h"
#include "knight_manager.h"
#include "monster_generator.h"
#include "knight_skill_q.h"
#include "knight_skill_e.h"
#include "arrow_dir.h"
#include "black_boss.h"
#include "boss_guide.h"
#include "mixsound_manager.h"
WorldMap::WorldMap()
{
    perlin_noise = new PerlinNoise();
    tile_kind[0] = TextureManager::LoadTexture("img/map_tiles/holewater.png");
    tile_kind[1] = TextureManager::LoadTexture("img/map_tiles/water.png");
    tile_kind[2] = TextureManager::LoadTexture("img/map_tiles/grass.png");
    tile_kind[3] = TextureManager::LoadTexture("img/map_tiles/grassmushroom0.png");
    tile_kind[4] = TextureManager::LoadTexture("img/map_tiles/grassmushroom1.png");
    tile_kind[5] = TextureManager::LoadTexture("img/map_tiles/tree.png");
    tmp_src.x = tmp_src.y = 0;
    tmp_src.h = tmp_src.w = 32;
}

WorldMap::~WorldMap()
{
    delete perlin_noise;
    for (int i = 0; i < 6; i++) SDL_DestroyTexture(tile_kind[i]);
}

int WorldMap::GetTilekind(int x, int y)
{
    double val = perlin_noise->GetPerlinNoise2D(x, y);
    if (val < 0.09)
        return 0; // hole_water
    if (val < 0.3)
        return 1; // water
    if (val < 0.70)
        return 2; // grass
    if (val < 0.75)
        return 3; // grass mushroom 0
    if (val < 0.80)
        return 4; // grass mushroom 1
    return 5; // tree
}

void WorldMap::Update()
{
    std::pair<int, int> dir = { 0, 0 };
    if (Game::keyboard_state[SDL_SCANCODE_SPACE])
    {
        if (knight->dir)
            knight->graphics->UseAnimation("sword_right");
        else
            knight->graphics->UseAnimation("sword_left");
        for (MonsterSke*& e : monster_genera->skeleton_list)
        {
            int x0 = e->movement->x - knight->x_diff - dir.first * static_cast<int> (knight->movement->speed) + 20;
            int y0 = e->movement->y - knight->y_diff - dir.second * static_cast<int> (knight->movement->speed) + 6;
            int x1 = x0 + 30;
            int y1 = y0 + 20;
            if (knight->dir && knight->CollidesSwordR(x0, y0, x1, y1))
            {
                e->DecreseHealth(knight->attack);

            }
            else if (!knight->dir && knight->CollidesSwordL(x0, y0, x1, y1))
            {
                e->DecreseHealth(knight->attack);
            }
        }
        if (boss->IsActiveZone())
        {
            int x0 = boss->movement->x - knight->x_diff + 20;
            int y0 = boss->movement->y - knight->y_diff + 30;
            int x1 = x0 + 50;
            int y1 = y0 + 60;
            if (knight->dir && knight->CollidesSwordR(x0, y0, x1, y1))
            {
                boss->DecreaseHealth(knight->attack);

            }
            else if (!knight->dir && knight->CollidesSwordL(x0, y0, x1, y1))
            {
                boss->DecreaseHealth(knight->attack);
            }
        }
        sound_manager->PlaySlash();
        return;
    }
    if (Game::keyboard_state[SDL_SCANCODE_LEFT] && Game::keyboard_state[SDL_SCANCODE_UP])
    {
        dir = { -1, -1 };
        knight->dir = 0;
        knight->graphics->UseAnimation("walk_left");
        goto Finished;
    }
    if (Game::keyboard_state[SDL_SCANCODE_RIGHT] && Game::keyboard_state[SDL_SCANCODE_UP])
    {
        dir = { 1, -1 };
        knight->dir = 1;
        knight->graphics->UseAnimation("walk_right");
        goto Finished;
    }
    if (Game::keyboard_state[SDL_SCANCODE_LEFT] && Game::keyboard_state[SDL_SCANCODE_DOWN])
    {
        dir = { -1, 1 };
        knight->dir = 0;
        knight->graphics->UseAnimation("walk_left");
        goto Finished;
    }
    if (Game::keyboard_state[SDL_SCANCODE_RIGHT] && Game::keyboard_state[SDL_SCANCODE_DOWN])
    {
        dir = { 1, 1 };
        knight->dir = 1;
        knight->graphics->UseAnimation("walk_right");
        goto Finished;
    }
    if (Game::keyboard_state[SDL_SCANCODE_UP])
    {
        dir = { 0, -1 };
        goto Next;
    }
    if (Game::keyboard_state[SDL_SCANCODE_DOWN])
    {
        dir = { 0, 1 };
        goto Next;
    }
    if (Game::keyboard_state[SDL_SCANCODE_LEFT])
    {
        dir = { -1, 0 };
        knight->dir = 0;
        knight->graphics->UseAnimation("walk_left");
        goto Finished;
    }
    if (Game::keyboard_state[SDL_SCANCODE_RIGHT])
    {
        dir = { 1, 0 };
        knight->dir = 1;
        knight->graphics->UseAnimation("walk_right");
        goto Finished;
    }
Next:;
    if (knight->dir)
        knight->graphics->UseAnimation("idle_right");
    else
        knight->graphics->UseAnimation("idle_left");
Finished:;

    if (dir.first != 0 || dir.second != 0)
        arrow_direct->ResetDirection(dir.first, dir.second);
    arrow_direct->Updated();

    bool valid_move = IsMove(dir);

    if (valid_move == false)
    {
        int tem_first = dir.first;
        int tem_second = dir.second;
        dir.second = 0;
        valid_move = IsMove(dir);
        if (valid_move == false)
        {
            dir.first = 0;
            dir.second = tem_second;
            valid_move = IsMove(dir);
            if (valid_move == false) dir = { 0, 0 };
        }
    }
    if (knight->dir)
        knight->graphics->UseAnimation("idle_right");
    else
        knight->graphics->UseAnimation("idle_left");
    knight->x_diff += dir.first * static_cast<int> (knight->movement->speed);
    knight->y_diff += dir.second * static_cast<int> (knight->movement->speed);

    if (Game::keyboard_state[SDL_SCANCODE_Q])
        knight_skill_q->ExecuteSkill(arrow_direct->Dx, arrow_direct->Dy);
    if (Game::keyboard_state[SDL_SCANCODE_E])
        knight_skill_e->ExecuteSkill();
    if (Game::keyboard_state[SDL_SCANCODE_A])
        boss_guides->actives = true;
    sound_manager->HandleToggle(Game::keyboard_state[SDL_SCANCODE_S], Game::keyboard_state[SDL_SCANCODE_D]);
}
void WorldMap::MapGrass()
{
    tmp_dest.h = tmp_dest.w = 32;
    for (int x = 0; x < 800; x += 32)
        for (int y = 0; y < 640; y += 32)
        {
            tmp_dest.x = x;
            tmp_dest.y = y;
            TextureManager::Draw(tile_kind[2], tmp_src, tmp_dest);
        }
}
void WorldMap::Render()
{
    int x_left = -((knight->x_diff % 32 + 32) % 32);
    int y_left = -((knight->y_diff % 32 + 32) % 32);
    int X_tile = (knight->x_diff / 32) + ((x_left != 0 && knight->x_diff < 0) ? -1 : 0);
    int Y_tile = (knight->y_diff / 32) + ((y_left != 0 && knight->y_diff < 0) ? -1 : 0);

    tmp_dest.h = tmp_dest.w = 32;

    std::vector<std::array<int, 2>> vector_tree;

    near_knight.clear();

    for (int x = x_left - 32, x_tile = X_tile - 1; x < 800; x += 32, x_tile++)
        for (int y = y_left - 32, y_tile = Y_tile - 1; y < 640; y += 32, y_tile++)
        {
            int tile = GetTilekind(x_tile, y_tile);
            if (GrassZone(x, y))
                tile = 2; // grass
            tmp_dest.x = x;
            tmp_dest.y = y;
            if (tile == 5)
            {
                TextureManager::Draw(tile_kind[4], tmp_src, tmp_dest);
                vector_tree.push_back({ x, y });
            }
            else
                TextureManager::Draw(tile_kind[tile], tmp_src, tmp_dest);
            bool tile_forbidden = (tile <= 1 || tile == 5);
            int sz = (tile == 5 ? 64 : 32);
            // May collide with knight
            if (tile_forbidden == true && knight->IsNearKnight(x, y, x + sz, y + sz))
            {
                near_knight.push_back({ x, y, sz });
            }
        }
    tmp_dest.h = tmp_dest.w = 64;
    for (auto& i : vector_tree)
    {
        tmp_dest.x = i[0];
        tmp_dest.y = i[1];
        TextureManager::Draw(tile_kind[5], tmp_src, tmp_dest);
    }

}

bool WorldMap::GrassZone(int x, int y)
{
    return knight->IsStartingZone(x, y)
        || boss->IsStartingZone(x, y);
}

bool WorldMap::IsMove(const std::pair<int, int>& dir)
{
    for (std::array<int, 3> &tile : near_knight)
    {
        int x0 = tile[0] - dir.first * static_cast<int> (knight->movement->speed) + (tile[2] == 64 ? 8 : 2);
        int y0 = tile[1] - dir.second * static_cast<int> (knight->movement->speed) + (tile[2] == 64 ? 10 : 3);
        int x1 = x0 + tile[2] - (tile[2] == 64 ? 8 : 4);
        int y1 = y0 + tile[2] - (tile[2] == 64 ? 30 : 20);
        if (knight->CollideWithKnight(x0, y0, x1, y1))
            return false;
    }
    for (MonsterSke*& e : monster_genera->skeleton_list)
    {
        int x0 = e->movement->x - knight->x_diff - dir.first * static_cast<int> (knight->movement->speed) + 20;
        int y0 = e->movement->y - knight->y_diff - dir.second * static_cast<int> (knight->movement->speed) + 6;
        int x1 = x0 + 30;
        int y1 = y0 + 20;
        if (knight->CollideWithKnight(x0, y0, x1, y1))
            return false;
    }
    return true;
}