#pragma once

#include "GameObject.h"

class Scene
{
public:
    Scene() = default;
    inline ~Scene()
    {
        for (const GameObject* go : mGameObjects)
        {
            delete go;
        }
        mGameObjects.clear();
    }

    [[nodiscard]] inline GameObject* CreateGameObject(const Vec2 position = Vec2{0.0f })
    {
        mGameObjects.emplace_back(new GameObject{ position });
        return mGameObjects.back();
    }

    inline void Update() const
    {
#if MT_EC
        //Todo.
#else // MT_EC
        for (GameObject* go : mGameObjects)
        {
            go->Update(0.0f);
        }
#endif // !MT_EC.
    }

    inline void Render(SDL_Renderer* renderer) const
    {
        for (GameObject* go : mGameObjects)
        {
            go->Render(renderer);
        }
    }

private:
    std::vector<GameObject*> mGameObjects;
};
