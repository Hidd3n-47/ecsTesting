#include "ecsTestingPch.h"
#include "GlobalVariables.h"

#include <SDL3/SDL_render.h>

void GlobalVariables::Init(SDL_Renderer* renderer)
{
    blankTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, 1, 1);

    SDL_Surface* surface = SDL_CreateSurface(1, 1, SDL_PIXELFORMAT_RGBA32);

    const uint32_t pixelColor = SDL_MapRGBA(SDL_GetPixelFormatDetails(surface->format), nullptr, 0xff, 0xff, 0xff, 0xff);

    uint32_t* pixels = static_cast<uint32_t*>(surface->pixels);
    *pixels = pixelColor;

    blankTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
}

void GlobalVariables::Destroy()
{
    SDL_DestroyTexture(blankTexture);
    blankTexture = nullptr;
}
