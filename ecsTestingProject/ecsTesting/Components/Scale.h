#pragma once

#include "EC/IComponent.h"

#ifndef ECS

class Scale : public IComponent
{
public:
    Vec2  scale = Vec2{ 1.0f, 1.0f };
};

#else

class Scale
{
public:
    Vec2  scale = Vec2{ 1.0f, 1.0f };
};

#endif