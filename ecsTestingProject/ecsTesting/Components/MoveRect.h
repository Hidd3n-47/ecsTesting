#pragma once
#include "EC/IComponent.h"

class COMPONENT(MoveRect) 
{
public:
    MoveRect() = default;
    MoveRect(const Vec2 direction);

#ifndef ECS
    void Update(const float dt) override;
#endif // !ECS.

    Vec2 mDirection = Vec2{ 0.05f, 0.05f };
};