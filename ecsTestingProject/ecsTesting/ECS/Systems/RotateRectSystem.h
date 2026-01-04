#pragma once

class RotateRect;
class Rotation;

class RotateRectSystem
{
public:
    static void Update(const RotateRect* moveRectArray, Rotation* rotates, const int size);
};
