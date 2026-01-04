#include "ecsTestingPch.h"
#include "MoveRect.h"

#include "GlobalVariables.h"
#include "EC/GameObject.h"

MoveRect::MoveRect(const Vec2 direction)
    : mDirection(direction)
{
    // Empty.
}

#ifndef ECS
void MoveRect::Update(const float dt)
{
    Position* position = mParent->GetComponent<Position>();
    position->position += mDirection;

    if (position->position.x <= 0.0f || position->position.x >= GlobalVariables::screenWidth)
    {
        mDirection.x *= -1.0f;
    }

    if (position->position.y <= 0.0f || position->position.y >= GlobalVariables::screenHeight)
    {
        mDirection.y *= -1.0f;
    }
}
#endif // !ECS.
