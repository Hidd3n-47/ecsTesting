#pragma once

struct SDL_Texture;
struct SDL_Renderer;

class GlobalVariables
{
public:
    static void Init(SDL_Renderer* renderer);
    static void Destroy();

    inline static SDL_Texture* blankTexture = nullptr;

    inline static float screenWidth         = 1920.0f;
    inline static float screenHeight        = 1080.0f;
};