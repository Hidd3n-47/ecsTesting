#pragma once

#include "EC/IComponent.h"

class COMPONENT(RectColor)
{
public:
    RectColor() = default;
    RectColor(const unsigned char r, const unsigned char g, const unsigned char b);

    unsigned char r, g, b;
};