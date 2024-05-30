#include "texture_manager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filename)
{
    SDL_Surface* tmpSurface = IMG_Load(filename);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect dest)
{
    SDL_RenderCopy(Game::renderer, texture, NULL, &dest);
}