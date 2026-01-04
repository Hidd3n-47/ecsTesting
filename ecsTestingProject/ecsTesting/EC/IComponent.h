#pragma once

struct SDL_Renderer;

class GameObject;

class IComponent
{
public:
    virtual ~IComponent() = default;

    virtual void OnComponentAdded(GameObject* parent) { mParent = parent; }
    virtual void OnComponentRemoved() { }

    virtual void Update(const float dt) { }
    virtual void Render(SDL_Renderer* renderer) { }

protected:
    GameObject* mParent = nullptr;
};