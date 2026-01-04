#include "ecsTestingPch.h"
#include "UpdateRectScale.h"

#include "EC/GameObject.h"

UpdateRectScale::UpdateRectScale(const float min, const float max, const float step)
    : mMinScale(min)
    , mMaxScale(max)
    , mStep(step)
{
    // Empty.
}

#ifndef ECS
void UpdateRectScale::Update(const float dt)
{
    Scale* scale = mParent->GetComponent<Scale>();

    float possibleNewScale;
    const float len = mMaxScale - mMinScale;

    if (mIncreasing)
    {
        const float t = (scale->scale.x - mMinScale) / len;

        possibleNewScale = mMinScale + (t + mStep) * len;

        mIncreasing = !(possibleNewScale >= mMaxScale);
        possibleNewScale = std::min(possibleNewScale, mMaxScale);
    }
    else
    {
        const float t = (mMaxScale - scale->scale.x) / len;

        possibleNewScale = mMaxScale - (t + mStep) * len;

        mIncreasing = (possibleNewScale <= mMinScale);
        possibleNewScale = std::max(possibleNewScale, mMinScale);
    }

    scale->scale = Vec2{ possibleNewScale };
}
#endif // !ECS.
