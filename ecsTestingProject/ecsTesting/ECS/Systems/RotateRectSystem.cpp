#include "ecsTestingPch.h"
#include "RotateRectSystem.h"

#include "Components/Rotation.h"
#include "Components/RotateRect.h"

#if !MT_ECS
void RotateRectSystem::Update(const RotateRect* rotateRectArray, Rotation* rotates, const int size)
{
    for (int i{ 0 }; i < size; ++i)
    {
        Rotation* rotation = &rotates[i];
        const RotateRect* rotate = &rotateRectArray[i];

        rotation->rotation += rotate->rotationAmount;
    }
}
#else // MT_ECS.
void RotateRectSystem::Init(RotateRect* rotateRectArray, Rotation* rotates, const int size)
{
    mRotateRectArray = rotateRectArray;
    mRotationArray = rotates;
    mSize = size;

    mThread = std::thread(Update);
}

void RotateRectSystem::Update()
{
    while (true)
    {
        if (!mUpdate) continue;

        mUpdate = false;
        mCompleted = false;

        for (int i{ 0 }; i < mSize; ++i)
        {
            Rotation* rotation = &mRotationArray[i];
            const RotateRect* rotate = &mRotateRectArray[i];

            rotation->rotation += rotate->rotationAmount;
        }

        mCompleted = true;
    }
}
#endif // MT_ECS.