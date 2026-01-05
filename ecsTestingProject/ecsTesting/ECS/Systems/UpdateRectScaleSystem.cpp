#include "ecsTestingPch.h"
#include "UpdateRectScaleSystem.h"

#include "Components/Scale.h"
#include "Components/UpdateRectScale.h"

#if !MT_ECS
void UpdateRectScaleSystem::Update(UpdateRectScale* updateRectArray, Scale* scales, const int size)
{
    for (int i{ 0 }; i < size; ++i)
    {
        Scale* scale = &scales[i];
        UpdateRectScale* rect = &updateRectArray[i];

        float possibleNewScale;
        const float len = rect->mMaxScale - rect->mMinScale;

        const float t = (scale->scale.x - rect->mMinScale) / len;

        possibleNewScale  = rect->mIncreasing ? rect->mMinScale + (t + rect->mStep) * len : rect->mMaxScale - (t + rect->mStep) * len;

        rect->mIncreasing = (possibleNewScale <= rect->mMinScale);

        possibleNewScale  = rect->mIncreasing ? std::min(possibleNewScale, rect->mMaxScale) : std::max(possibleNewScale, rect->mMinScale);

        scale->scale = Vec2{ possibleNewScale };
    }
}
#else // MT_ECS.
void UpdateRectScaleSystem::Init(UpdateRectScale* updateRectArray, Scale* scales, const int size)
{
    mScaleRectArray = updateRectArray;
    mScaleArray = scales;
    mSize = size;

    mThread = std::thread(Update);
}

void UpdateRectScaleSystem::Update()
{
    while (true)
    {
        if (!mUpdate) continue;

        mUpdate = false;
        mCompleted = false;

        for (int i{ 0 }; i < mSize; ++i)
        {
            Scale* scale = &mScaleArray[i];
            UpdateRectScale* rect = &mScaleRectArray[i];

            float possibleNewScale;
            const float len = rect->mMaxScale - rect->mMinScale;

            const float t = (scale->scale.x - rect->mMinScale) / len;

            possibleNewScale  = rect->mIncreasing ? rect->mMinScale + (t + rect->mStep) * len : rect->mMaxScale - (t + rect->mStep) * len;

            rect->mIncreasing = (possibleNewScale <= rect->mMinScale);

            possibleNewScale  = rect->mIncreasing ? std::min(possibleNewScale, rect->mMaxScale) : std::max(possibleNewScale, rect->mMinScale);

            scale->scale = Vec2{ possibleNewScale };
        }

        mCompleted = true;
    }
}
#endif // MT_ECS.
