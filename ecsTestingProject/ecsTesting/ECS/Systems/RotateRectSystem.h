#pragma once

class RotateRect;
class Rotation;

class RotateRectSystem
{
public:
#if !MT_ECS
    static void Update(const RotateRect* rotateRectArray, Rotation* rotates, const int size);
#else // MT_ECS.
    static void Init(RotateRect* rotateRectArray, Rotation* rotates, const int size);

    static void Update();

    inline static void ShouldUpdate() { mUpdate = true; }
    [[nodiscard]] inline static bool IsCompleted() { return mCompleted; }
private:
    inline static std::atomic<bool> mUpdate = false;
    inline static std::atomic<bool> mCompleted = true;

    inline static std::thread mThread;

    inline static RotateRect* mRotateRectArray = nullptr;
    inline static Rotation* mRotationArray = nullptr;
    inline static int mSize = 0;
#endif // MT_ECS.
};
