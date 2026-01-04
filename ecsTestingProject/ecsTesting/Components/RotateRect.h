#pragma once

#include "EC/IComponent.h"

class COMPONENT(RotateRect)
{
public:
    RotateRect() = default;
    RotateRect(const float direction);

#ifndef ECS
    void Update(const float dt) override;
#endif // !ECS.

    float rotationAmount = 0.00005f;
};