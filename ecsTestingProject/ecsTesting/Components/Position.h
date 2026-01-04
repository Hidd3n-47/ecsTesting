#pragma once

#include "EC/IComponent.h"

#ifndef ECS

class Position : public IComponent
{
public:
    Vec2  position = Vec2{ 0.0f, 0.0f };
};

#else

class Position
{
public:
    Vec2  position = Vec2{ 0.0f, 0.0f };
};

#endif