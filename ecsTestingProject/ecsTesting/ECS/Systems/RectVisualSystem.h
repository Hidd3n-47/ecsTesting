#pragma once

struct SDL_Renderer;

class Position;
class Rotation;
class Scale;
class RectVisual;
class RectColor;

class RectVisualSystem
{
public:
    static void Render(SDL_Renderer* renderer, const RectVisual* rectVisualArray, const RectColor* rectColors, const Position* positions, const Rotation* rotations, const Scale* scales, const int size);
};

