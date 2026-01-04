#include "ecsTestingPch.h"
#include "RectVisualSystem.h"

#include <SDL3/SDL_render.h>

#include "GlobalVariables.h"

#include "Components/Scale.h"
#include "Components/Position.h"
#include "Components/Rotation.h"
#include "Components/RectColor.h"
#include "Components/RectVisual.h"

void RectVisualSystem::Render(SDL_Renderer* renderer, const RectVisual* rectVisualArray, const RectColor* rectColors,  const Position* positions,  const Rotation* rotations, const Scale* scales, const int size)
{
    for (int i{ 0 }; i < size; ++i)
    {
        const Position*   position = &positions[i];
        const Rotation*   rotation = &rotations[i];
        const Scale*      scale    = &scales[i];
        const RectVisual* rect     = &rectVisualArray[i];
        const RectColor*  color    = &rectColors[i];

        SDL_SetTextureColorMod(GlobalVariables::blankTexture, color->r, color->g, color->b);

        constexpr SDL_FRect srcRect{ .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f };
        const     SDL_FRect dstRect{ position->position.x, position->position.y, rect->mSize.x * scale->scale.x, rect->mSize.y * scale->scale.y };

        SDL_RenderTextureRotated(renderer, GlobalVariables::blankTexture, &srcRect, &dstRect, rotation->rotation, nullptr, SDL_FLIP_NONE);

    }

    SDL_SetTextureColorMod(GlobalVariables::blankTexture, 0xff, 0xff, 0xff);
}
