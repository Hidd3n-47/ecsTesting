#include "ecsTestingPch.h"
#include "RotateRect.h"

#include "EC/GameObject.h"

RotateRect::RotateRect(const float direction)
    : rotationAmount(direction)
{
    // Empty.
}

#ifndef ECS
void RotateRect::Update(const float dt)
{
    Rotation* rotation = mParent->GetComponent<Rotation>();

    rotation->rotation += rotationAmount;
}
#endif // !ECS.
