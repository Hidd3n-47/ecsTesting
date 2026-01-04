#pragma once

class MoveRect;
class Position;

class MoveRectSystem
{
public:
    static void Update(MoveRect* moveRectArray, Position* positions, const int size);
};

