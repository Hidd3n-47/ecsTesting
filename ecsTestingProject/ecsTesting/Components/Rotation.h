#pragma once

#include "EC/IComponent.h"

#ifndef ECS

class Rotation : public IComponent
{
public:
    float rotation = 0.0f;
};

#else

class Rotation
{
public:
    float rotation = 0.0f;
};

#endif