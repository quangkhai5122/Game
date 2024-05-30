#include "world_map.h"
#include "player_manager.h"
#include "enemy_generator.h"
#include "player_skill_q.h"
#include "player_skill_e.h"
#include "arrow_direction.h"
#include "boss.h"
#include "boss_guider.h"
#include "sound_manager.h"
WorldMap::WorldMap()
{
    perlin_noise = new PerlinNoise();
    tile_type[0] = TextureManager::LoadTexture("img/map_tiles/deep_water.png");
    tile_type[1] = TextureManager::LoadTexture("img/map_tiles/water.png");
    tile_type[2] = TextureManager::LoadTexture("img/map_tiles/grass.png");
    tile_type[3] = TextureManager::LoadTexture("img/map_tiles/grass_mushroom_0.png");
    tile_type[4] = TextureManager::LoadTexture("img/map_tiles/grass_mushroom_1.png");
    tile_type[5] = TextureManager::LoadTexture("img/map_tiles/tree.png");
    tmp_src.x = tmp_src.y = 0;
    tmp_src.h = tmp_src.w = 32;
}

WorldMap::~WorldMap()
{
    delete perlin_noise;
    for (int i = 0; i < 6; i++) SDL_DestroyTexture(tile_type[i]);
}

int WorldMap::GetTileType(int x, int y)
{
    double val = perlin_noise->GetPerlinNoise2D(x, y);
    if (val < 0.09)
        return 0; // deep_water
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

void WorldMap::UpdateMap()
{
    std::pair<int, int> dir = { 0, 0 };
    if (Game::keyboard_state[SDL_SCANCODE_SPACE])
    {
        if (player->direction)
            player->sprite->ApplyAnimation("sword_right");
        else
            player->sprite->ApplyAnimation("sword_left");
        for (EnemySkeleton*& e : enemy_generator->skeleton_container)
        {
            int x0 = e->transform->x - player->xdif - dir.first * static_cast<int> (player->transform->speed) + 20;
            int y0 = e->transform->y - player->ydif - dir.second * static_cast<int> (player->transform->speed) + 6;
            int x1 = x0 + 30;
            int y1 = y0 + 20;
            if (player->direction && player->CollideSwordRight(x0, y0, x1, y1))
            {
                e->DecHealth(player->attack);

            }
            else if (!player->direction && player->CollideSwordLeft(x0, y0, x1, y1))
            {
                e->DecHealth(player->attack);
            }
        }
        if (boss->IsInsideActiveZone())
        {
            int x0 = boss->transform->x - player->xdif + 20;
            int y0 = boss->transform->y - player->ydif + 30;
            int x1 = x0 + 50;
            int y1 = y0 + 60;
            if (player->direction && player->CollideSwordRight(x0, y0, x1, y1))
            {
                boss->DecHealth(player->attack);

            }
            else if (!player->direction && player->CollideSwordLeft(x0, y0, x1, y1))
            {
                boss->DecHealth(player->attack);
            }
        }
        sound_manager->PlaySlash();
        return;
    }
    if (Game::keyboard_state[SDL_SCANCODE_LEFT] && Game::keyboard_state[SDL_SCANCODE_UP])
    {
        dir = { -1, -1 };
        player->direction = 0;
        player->sprite->ApplyAnimation("walk_left");
        goto Finished;
    }
    if (Game::keyboard_state[SDL_SCANCODE_RIGHT] && Game::keyboard_state[SDL_SCANCODE_UP])
    {
        dir = { 1, -1 };
        player->direction = 1;
        player->sprite->ApplyAnimation("walk_right");
        goto Finished;
    }
    if (Game::keyboard_state[SDL_SCANCODE_LEFT] && Game::keyboard_state[SDL_SCANCODE_DOWN])
    {
        dir = { -1, 1 };
        player->direction = 0;
        player->sprite->ApplyAnimation("walk_left");
        goto Finished;
    }
    if (Game::keyboard_state[SDL_SCANCODE_RIGHT] && Game::keyboard_state[SDL_SCANCODE_DOWN])
    {
        dir = { 1, 1 };
        player->direction = 1;
        player->sprite->ApplyAnimation("walk_right");
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
        player->direction = 0;
        player->sprite->ApplyAnimation("walk_left");
        goto Finished;
    }
    if (Game::keyboard_state[SDL_SCANCODE_RIGHT])
    {
        dir = { 1, 0 };
        player->direction = 1;
        player->sprite->ApplyAnimation("walk_right");
        goto Finished;
    }
Next:;
    if (player->direction)
        player->sprite->ApplyAnimation("idle_right");
    else
        player->sprite->ApplyAnimation("idle_left");
Finished:;

    if (dir.first != 0 || dir.second != 0)
        arrow_direction->ResetDirection(dir.first, dir.second);
    arrow_direction->Update();

    bool valid_move = IsValidMove(dir);

    if (valid_move == false)
    {
        int tem_first = dir.first;
        int tem_second = dir.second;
        dir.second = 0;
        valid_move = IsValidMove(dir);
        if (valid_move == false)
        {
            dir.first = 0;
            dir.second = tem_second;
            valid_move = IsValidMove(dir);
            if (valid_move == false) dir = { 0, 0 };
        }
    }
    if (player->direction)
        player->sprite->ApplyAnimation("idle_right");
    else
        player->sprite->ApplyAnimation("idle_left");
    player->xdif += dir.first * static_cast<int> (player->transform->speed);
    player->ydif += dir.second * static_cast<int> (player->transform->speed);

    if (Game::keyboard_state[SDL_SCANCODE_Q])
        player_skill_q->ExecuteSkill(arrow_direction->dx, arrow_direction->dy);
    if (Game::keyboard_state[SDL_SCANCODE_E])
        player_skill_e->ExecuteSkill();
    if (Game::keyboard_state[SDL_SCANCODE_A])
        boss_guider->active = true;
    sound_manager->HandleToggle(Game::keyboard_state[SDL_SCANCODE_S], Game::keyboard_state[SDL_SCANCODE_D]);
}
void WorldMap::RenderMapFullGrass()
{
    tmp_dest.h = tmp_dest.w = 32;
    for (int x = 0; x < 800; x += 32)
        for (int y = 0; y < 640; y += 32)
        {
            tmp_dest.x = x;
            tmp_dest.y = y;
            TextureManager::Draw(tile_type[2], tmp_src, tmp_dest);
        }
}
void WorldMap::RenderMap()
{
    int x_left = -((player->xdif % 32 + 32) % 32);
    int y_left = -((player->ydif % 32 + 32) % 32);
    int X_tile = (player->xdif / 32) + ((x_left != 0 && player->xdif < 0) ? -1 : 0);
    int Y_tile = (player->ydif / 32) + ((y_left != 0 && player->ydif < 0) ? -1 : 0);

    tmp_dest.h = tmp_dest.w = 32;

    std::vector<std::array<int, 2>> vec_tree;

    tiles_near_player.clear();

    for (int x = x_left - 32, x_tile = X_tile - 1; x < 800; x += 32, x_tile++)
        for (int y = y_left - 32, y_tile = Y_tile - 1; y < 640; y += 32, y_tile++)
        {
            int tile = GetTileType(x_tile, y_tile);
            if (InsideGrassZone(x, y))
                tile = 2; // grass
            tmp_dest.x = x;
            tmp_dest.y = y;
            if (tile == 5)
            {
                TextureManager::Draw(tile_type[4], tmp_src, tmp_dest);
                vec_tree.push_back({ x, y });
            }
            else
                TextureManager::Draw(tile_type[tile], tmp_src, tmp_dest);
            bool tile_forbidden = (tile <= 1 || tile == 5);
            int sz = (tile == 5 ? 64 : 32);
            // May collide with player
            if (tile_forbidden == true && player->IsNearPlayer(x, y, x + sz, y + sz))
            {
                tiles_near_player.push_back({ x, y, sz });
            }
        }
    tmp_dest.h = tmp_dest.w = 64;
    for (auto& i : vec_tree)
    {
        tmp_dest.x = i[0];
        tmp_dest.y = i[1];
        TextureManager::Draw(tile_type[5], tmp_src, tmp_dest);
    }

}

bool WorldMap::InsideGrassZone(int x, int y)
{
    return player->IsInsideStartingZone(x, y)
        || boss->IsInsideStartingZone(x, y);
}

bool WorldMap::IsValidMove(const std::pair<int, int>& dir)
{
    for (std::array<int, 3> &tile : tiles_near_player)
    {
        int x0 = tile[0] - dir.first * static_cast<int> (player->transform->speed) + (tile[2] == 64 ? 8 : 2);
        int y0 = tile[1] - dir.second * static_cast<int> (player->transform->speed) + (tile[2] == 64 ? 10 : 3);
        int x1 = x0 + tile[2] - (tile[2] == 64 ? 8 : 4);
        int y1 = y0 + tile[2] - (tile[2] == 64 ? 30 : 20);
        if (player->CollidePlayer(x0, y0, x1, y1))
            return false;
    }
    for (EnemySkeleton*& e : enemy_generator->skeleton_container)
    {
        int x0 = e->transform->x - player->xdif - dir.first * static_cast<int> (player->transform->speed) + 20;
        int y0 = e->transform->y - player->ydif - dir.second * static_cast<int> (player->transform->speed) + 6;
        int x1 = x0 + 30;
        int y1 = y0 + 20;
        if (player->CollidePlayer(x0, y0, x1, y1))
            return false;
    }
    return true;
}