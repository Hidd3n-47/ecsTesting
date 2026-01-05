#pragma once

class MoveRect;
class Position;

class MoveRectSystem
{
public:
#if !MT_ECS
    static void Update(MoveRect* moveRectArray, Position* positions, const int size);
#else // MT_ECS.
    static void Init(MoveRect* moveRectArray, Position* positions, const int size);

    static void Update();

    inline static void ShouldUpdate() { mUpdate = true; }
    [[nodiscard]] inline static bool IsCompleted() { return mCompleted; }
private:
    inline static std::atomic<bool> mUpdate = false;
    inline static std::atomic<bool> mCompleted = true;

    inline static std::thread mThread;

    inline static MoveRect* mMoveRectArray = nullptr;
    inline static Position* mPositionArray = nullptr;
    inline static int mSize = 0;
#endif // MT_ECS.
};

