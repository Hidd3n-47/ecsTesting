#pragma once

#include "EC/IComponent.h"

class COMPONENT(RectVisual)
{
public:
    RectVisual() = default;
    RectVisual(const Vec2 size);

#ifndef ECS
    void Render(SDL_Renderer* renderer) override;
#endif // !ECS.

    Vec2 mSize = Vec2{ 15.0f, 15.0f };
};

