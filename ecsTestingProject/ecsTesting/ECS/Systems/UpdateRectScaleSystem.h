#pragma once

class Scale;
class UpdateRectScale;

class UpdateRectScaleSystem
{
public:
    static void Update(UpdateRectScale* updateRectArray, Scale* scales, const int size);
};

