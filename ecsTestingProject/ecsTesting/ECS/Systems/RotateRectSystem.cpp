#include "ecsTestingPch.h"
#include "RotateRectSystem.h"

#include "Components/Rotation.h"
#include "Components/RotateRect.h"

void RotateRectSystem::Update(const RotateRect* moveRectArray, Rotation* rotates, const int size)
{
    for (int i{ 0 }; i < size; ++i)
    {
        Rotation* rotation = &rotates[i];
        const RotateRect* rotate = &moveRectArray[i];

        rotation->rotation += rotate->rotationAmount;
    }
}
