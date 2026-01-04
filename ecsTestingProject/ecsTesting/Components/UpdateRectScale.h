#pragma once
#include "EC/IComponent.h"

class COMPONENT(UpdateRectScale)
{
public:
    UpdateRectScale() = default;
    UpdateRectScale(const float min, const float max, const float step);

#ifndef ECS
    void Update(const float dt) override;
#endif // !ECS.

    float mMinScale   = 0.2f;
    float mMaxScale   = 1.8f;
    float mStep       = 0.00002f;
    bool  mIncreasing = false;
};
