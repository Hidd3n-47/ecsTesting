#include "ecsTestingPch.h"
#include "MoveRectSystem.h"

#include "GlobalVariables.h"

#include "Components/MoveRect.h"
#include "Components/Position.h"

#if !MT_ECS
void MoveRectSystem::Update(MoveRect* moveRectArray, Position* positions, const int size)
{
    for (int i{ 0 }; i < size; ++i)
    {
        Position* position = &positions[i];
        MoveRect* moveRect = &moveRectArray[i];

        position->position += moveRect->mDirection;

        bool changeDirection = position->position.x <= 0.0f || position->position.x >= GlobalVariables::screenWidth;
        moveRect->mDirection.x *= changeDirection ? -1.0f : 1.0f;

        changeDirection = position->position.y <= 0.0f || position->position.y >= GlobalVariables::screenHeight;
        moveRect->mDirection.y *= changeDirection ? -1.0f : 1.0f;
    }
}
#else // MT_ECS.
void MoveRectSystem::Init(MoveRect* moveRectArray, Position* positions, const int size)
{
    mMoveRectArray = moveRectArray;
    mPositionArray = positions;
    mSize = size;

    mThread = std::thread(Update);
}

void MoveRectSystem::Update()
{
    while (true)
    {
        if (!mUpdate)
        {
            continue;
        }

        mUpdate = false;
        mCompleted = false;

        for (int i{ 0 }; i < mSize; ++i)
        {
            Position* position = &mPositionArray[i];
            MoveRect* moveRect = &mMoveRectArray[i];

            position->position += moveRect->mDirection;

            bool changeDirection = position->position.x <= 0.0f || position->position.x >= GlobalVariables::screenWidth;
            moveRect->mDirection.x *= changeDirection ? -1.0f : 1.0f;

            changeDirection = position->position.y <= 0.0f || position->position.y >= GlobalVariables::screenHeight;
            moveRect->mDirection.y *= changeDirection ? -1.0f : 1.0f;
        }

        mCompleted = true;
    }
}
#endif // MT_ECS.