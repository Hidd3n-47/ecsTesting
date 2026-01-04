#include "ecsTestingPch.h"
#include "UpdateRectScaleSystem.h"

#include "Components/Scale.h"
#include "Components/UpdateRectScale.h"

void UpdateRectScaleSystem::Update(UpdateRectScale* updateRectArray, Scale* scales, const int size)
{
    for (int i{ 0 }; i < size; ++i)
    {
        Scale* scale = &scales[i];
        UpdateRectScale* rect = &updateRectArray[i];

        float possibleNewScale;
        const float len = rect->mMaxScale - rect->mMinScale;

        if (rect->mIncreasing)
        {
            const float t = (scale->scale.x - rect->mMinScale) / len;

            possibleNewScale = rect->mMinScale + (t + rect->mStep) * len;

            rect->mIncreasing = !(possibleNewScale >= rect->mMaxScale);
            possibleNewScale = std::min(possibleNewScale, rect->mMaxScale);
        }
        else
        {
            const float t = (rect->mMaxScale - scale->scale.x) / len;

            possibleNewScale = rect->mMaxScale - (t + rect->mStep) * len;

            rect->mIncreasing = (possibleNewScale <= rect->mMinScale);
            possibleNewScale = std::max(possibleNewScale, rect->mMinScale);
        }

        scale->scale = Vec2{ possibleNewScale };
    }
}