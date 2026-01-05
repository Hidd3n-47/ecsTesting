#include "ecsTestingPch.h"

#include <charconv>
#include "RunningAverage.h"

static constexpr int TEST_SIZE = 2'000;

#if !ECS_TEST
#include <SDL3/SDL.h>

#include "GlobalVariables.h"

#include "EC/Scene.h"

#include "Components/MoveRect.h"
#include "Components/RectColor.h"
#include "Components/RectVisual.h"
#include "Components/RotateRect.h"
#include "Components/UpdateRectScale.h"

namespace
{

void Input(bool& running)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_EVENT_QUIT:
            running = false;
            break;
        }
    }
}

void Update(const Scene& scene)
{
    scene.Update();
}

void Render(SDL_Renderer* renderer, const Scene& scene)
{
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    scene.Render(renderer);

    SDL_RenderPresent(renderer);
}

} // Anonymous namespace.

int main(int, char**)
{
    srand(time(nullptr));

    RunningAverage fpsAverage;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("ECS Testing", GlobalVariables::screenWidth, GlobalVariables::screenHeight, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    Scene scene;

    for (uint32_t i{ 0 }; i < TEST_SIZE; ++i)
    {
        const float x  = (rand() % (int)GlobalVariables::screenWidth);
        const float y  = (rand() % (int)GlobalVariables::screenHeight);
        GameObject* go = scene.CreateGameObject(Vec2{ x, y });

        const float rectSize = rand() % 30;
        go->AddComponent<RectVisual>(Vec2{ rectSize });

        const unsigned char r = rand() % 255;
        const unsigned char g = rand() % 255;
        const unsigned char b = rand() % 255;
        go->AddComponent<RectColor>(r, g, b);

        const float directionX = (rand() % 200) / 100.0f - 100.0f * 0.0f;
        const float directionY = (rand() % 200) / 100.0f - 100.0f * 0.0f;
        go->AddComponent<MoveRect>(Vec2{ directionX, directionY });

        const float rotation = (rand() % 20) / 100.0f;
        go->AddComponent<RotateRect>(rotation);

        const float min  = (rand() % 8) / 10.0f + 0.2f;
        const float max  = (rand() % 3) / 10.0f + 1.0f;
        const float step = (rand() % 5) / 10'000.0f;
        go->AddComponent<UpdateRectScale>(min, max, step);
    }

    GlobalVariables::Init(renderer);

    bool running = true;
    while (running)
    {
        auto startTime = SDL_GetPerformanceCounter();

        Input(running);

        Update(scene);

#if GFX
        Render(renderer, scene);
#endif // GFX.

        const uint64_t now = SDL_GetPerformanceCounter();

        auto dt = static_cast<float>(now - startTime) / static_cast<float>(SDL_GetPerformanceFrequency());
        fpsAverage.UpdateAverage(dt);
        // Max frames displayed as: 1234.123 <- total of 8 characters + 1 for null terminating character.
#if FPS_TITLE
        char title[9];
        std::to_chars(title, title + sizeof(title), 1.0 / fpsAverage.average, std::chars_format::fixed, 3);
        title[sizeof(title) - 1] = '\0';
        SDL_SetWindowTitle(window, title);
#endif // FPS_TITLE.
    }
#if !FPS_TITLE
    std::cout << "Average fps for duration: " << 1.0 / fpsAverage.average << "\n";
#endif // FPS_TITLE.

    GlobalVariables::Destroy();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
#else // ECS_TEST.

#include <SDL3/SDL.h>

#include "GlobalVariables.h"

#include "ECS/Systems/MoveRectSystem.h"
#include "ECS/Systems/RotateRectSystem.h"
#include "ECS/Systems/RectVisualSystem.h"
#include "ECS/Systems/UpdateRectScaleSystem.h"

#include "Components/Position.h"
#include "Components/Rotation.h"
#include "Components/Scale.h"
#include "Components/MoveRect.h"
#include "Components/RotateRect.h"
#include "Components/RectColor.h"
#include "Components/RectVisual.h"
#include "Components/UpdateRectScale.h"

namespace
{

void Input(bool& running)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_EVENT_QUIT:
            running = false;
            break;
        }
    }
}

void Update(Position* positions, Rotation* rotations, Scale* scales, MoveRect* moveRects, const RotateRect* rotateRects, UpdateRectScale* scaleRects)
{
#if MT_ECS
    MoveRectSystem::ShouldUpdate();
    UpdateRectScaleSystem::ShouldUpdate();
    RotateRectSystem::ShouldUpdate();

    while (!MoveRectSystem::IsCompleted() || !UpdateRectScaleSystem::IsCompleted() || !RotateRectSystem::IsCompleted()) {}
#else // MT_ECS.
    MoveRectSystem::Update(moveRects, positions, TEST_SIZE);
    UpdateRectScaleSystem::Update(scaleRects, scales, TEST_SIZE);
    RotateRectSystem::Update(rotateRects, rotations, TEST_SIZE);
#endif // !MT_ECS.

}

void Render(SDL_Renderer* renderer, const RectVisual* rectVisualArray, const RectColor* rectColors, const Position* positions, const Rotation* rotations, const Scale* scales)
{
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);

    RectVisualSystem::Render(renderer, rectVisualArray, rectColors, positions, rotations, scales, TEST_SIZE);

    SDL_RenderPresent(renderer);
}

} // Anonymous namespace.

int main(int, char**)
{
    srand(time(nullptr));

    RunningAverage fpsAverage;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("ECS Testing", GlobalVariables::screenWidth, GlobalVariables::screenHeight, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);

    Position*           positions   = new Position[TEST_SIZE];
    Rotation*           rotations   = new Rotation[TEST_SIZE];
    Scale*              scales      = new Scale[TEST_SIZE];
    RectVisual*         rectVisuals = new RectVisual[TEST_SIZE];
    RectColor*          rectColors  = new RectColor[TEST_SIZE];
    MoveRect*           moveRects   = new MoveRect[TEST_SIZE];
    RotateRect*         rotateRects = new RotateRect[TEST_SIZE];
    UpdateRectScale*    scaleRects  = new UpdateRectScale[TEST_SIZE];

    for (uint32_t i{ 0 }; i < TEST_SIZE; ++i)
    {
        const float x = (rand() % (int)GlobalVariables::screenWidth);
        const float y = (rand() % (int)GlobalVariables::screenHeight);
        positions[i].position.x = x;
        positions[i].position.y = y;

        const float rectSize = rand() % 30;
        rectVisuals[i].mSize = Vec2{ rectSize };

        rectColors[i].r = rand() % 255;
        rectColors[i].g = rand() % 255;
        rectColors[i].b = rand() % 255;

        const float directionX = (rand() % 200) / 100.0f - 100.0f * 0.0f;
        const float directionY = (rand() % 200) / 100.0f - 100.0f * 0.0f;
        moveRects[i].mDirection = Vec2{ directionX, directionY };

        const float rotation = (rand() % 20) / 100.0f;
        rotateRects[i].rotationAmount = rotation;

        const float min = (rand() % 8) / 10.0f + 0.2f;
        const float max = (rand() % 3) / 10.0f + 1.0f;
        const float step = (rand() % 5) / 10'000.0f;
        scaleRects->mMinScale = min;
        scaleRects->mMaxScale = max;
        scaleRects->mStep = step;
    }

    GlobalVariables::Init(renderer);

#if MT_ECS
    MoveRectSystem::Init(moveRects, positions, TEST_SIZE);
    UpdateRectScaleSystem::Init(scaleRects, scales, TEST_SIZE);
    RotateRectSystem::Init(rotateRects, rotations, TEST_SIZE);
#endif // MT_ECS.

    bool running = true;
    while (running)
    {
        auto startTime = SDL_GetPerformanceCounter();

        Input(running);

        Update(positions, rotations, scales, moveRects, rotateRects, scaleRects);

#if GFX
        Render(renderer, rectVisuals, rectColors, positions, rotations, scales);
#endif // GFX.

        const uint64_t now = SDL_GetPerformanceCounter();

        auto dt = static_cast<float>(now - startTime) / static_cast<float>(SDL_GetPerformanceFrequency());
        fpsAverage.UpdateAverage(dt);
        // Max frames displayed as: 1234.123 <- total of 8 characters + 1 for null terminating character.
#if FPS_TITLE
        char title[9];
        std::to_chars(title, title + sizeof(title), 1.0 / fpsAverage.average, std::chars_format::fixed, 3);
        title[sizeof(title) - 1] = '\0';
        SDL_SetWindowTitle(window, title);
#endif // FPS_TITLE.
    }
#if !FPS_TITLE
    std::cout << "Average fps for duration: " << 1.0 / fpsAverage.average << "\n";
#endif // FPS_TITLE.

    GlobalVariables::Destroy();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
#endif // ECS_TEST.