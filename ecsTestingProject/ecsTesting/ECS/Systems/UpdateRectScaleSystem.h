#pragma once

class Scale;
class UpdateRectScale;

class UpdateRectScaleSystem
{
public:
#if !MT_ECS
    static void Update(UpdateRectScale* updateRectArray, Scale* scales, const int size);
#else // MT_ECS.
    static void Init(UpdateRectScale* updateRectArray, Scale* scales, const int size);

    static void Update();

    inline static void ShouldUpdate() { mUpdate = true; }
    [[nodiscard]] inline static bool IsCompleted() { return mCompleted; }
private:
    inline static std::atomic<bool> mUpdate = false;
    inline static std::atomic<bool> mCompleted = true;

    inline static std::thread mThread;

    inline static UpdateRectScale* mScaleRectArray = nullptr;
    inline static Scale* mScaleArray = nullptr;
    inline static int mSize = 0;
#endif // MT_ECS.
};
