#include "ecsTestingPch.h"
#include "GameObject.h"

#include "IComponent.h"

#ifndef ECS

void GameObject::Update(const float dt) const
{
    for (IComponent* component : mComponents)
    {
        component->Update(dt);
    }
}

void GameObject::Render(SDL_Renderer* renderer) const
{
    for (IComponent* component : mComponents)
    {
        component->Render(renderer);
    }
}

#endif // ECS.