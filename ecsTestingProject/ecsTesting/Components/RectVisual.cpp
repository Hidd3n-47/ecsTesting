#include "ecsTestingPch.h"
#include "RectVisual.h"

#include <SDL3/SDL_render.h>

#include "EC/GameObject.h"
#include "src/GlobalVariables.h"

#include "Components/RectColor.h"

RectVisual::RectVisual(const Vec2 size) 
    : mSize(size)
{
    // Empty.
}

#ifndef ECS
void RectVisual::Render(SDL_Renderer* renderer)
{
    const Position* position = mParent->GetComponent<Position>();
    const Rotation* rotation = mParent->GetComponent<Rotation>();
    const Scale*    scale    = mParent->GetComponent<Scale>();

    const RectColor* color = mParent->GetComponent<RectColor>();

    SDL_SetTextureColorMod(GlobalVariables::blankTexture, color->r, color->g, color->b);

    constexpr SDL_FRect srcRect{ .x = 0.0f, .y = 0.0f, .w = 1.0f, .h = 1.0f };
    const     SDL_FRect dstRect{ position->position.x, position->position.y, mSize.x * scale->scale.x, mSize.y * scale->scale.y };

    SDL_RenderTextureRotated(renderer, GlobalVariables::blankTexture, &srcRect, &dstRect, rotation->rotation, nullptr, SDL_FLIP_NONE);

    SDL_SetTextureColorMod(GlobalVariables::blankTexture, 0xff, 0xff, 0xff);
}
#endif // !ECS.
