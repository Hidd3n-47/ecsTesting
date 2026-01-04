#pragma once

#ifndef ECS
#include "Components/Position.h"
#include "Components/Rotation.h"
#include "Components/Scale.h"

struct SDL_Renderer;

class IComponent;

class GameObject
{
public:
    GameObject(const Vec2 position);
    virtual ~GameObject() = default;

    void Update(const float dt) const;
    void Render(SDL_Renderer* renderer) const;

    template <typename Component>
    Component* AddComponent();

    template <typename Component, typename... Args>
    Component* AddComponent(Args ...args);

    template <typename Component>
    void RemoveComponent();

    template <typename Component>
    [[nodiscard]] Component* GetComponent() const;

    [[nodiscard]] inline const std::vector<IComponent*>& GetComponents() const { return mComponents; }

private:
    std::vector<IComponent*> mComponents;

    //std::unordered_map<std::string, int> mComponentNameToIndex;
};

inline GameObject::GameObject(const Vec2 position)
{
    AddComponent<Position>()->position = position;
    AddComponent<Rotation>();
    AddComponent<Scale>();
}

template <typename Component>
inline Component* GameObject::AddComponent()
{
    mComponents.emplace_back(new Component());

    mComponents.back()->OnComponentAdded(this);

    //mComponentNameToIndex[typeid(Component).name()] = mComponents.size() - 1;

    return reinterpret_cast<Component*>(mComponents.back());
}

template <typename Component, typename... Args>
inline Component* GameObject::AddComponent(Args ...args)
{
    mComponents.emplace_back(new Component(std::forward<Args>(args)...));

    mComponents.back()->OnComponentAdded(this);

    //mComponentNameToIndex[typeid(Component).name()] = mComponents.size() - 1;

    return reinterpret_cast<Component*>(mComponents.back());
}

template <typename Component>
void GameObject::RemoveComponent()
{
    for (auto it{ mComponents.begin() }; it != mComponents.end(); ++it)
    {
        if (Component* castComponent = dynamic_cast<Component*>(*it); castComponent != nullptr)
        {
            std::erase(mComponents, castComponent);
            castComponent->OnComponentRemoved();

            mComponents.erase(it);

            delete castComponent;
            return;
        }
    }
}

template <typename Component>
inline Component* GameObject::GetComponent() const
{
    //const int t = mComponentNameToIndex.at(typeid(Component).name());
    //return dynamic_cast<Component*>(mComponents[t]);

    for (IComponent* comp : mComponents)
    {
        if (Component* castComponent = dynamic_cast<Component*>(comp); castComponent != nullptr)
        {
            return castComponent;
        }
    }

    return nullptr;
}

#endif // ECS.