#include "GameObject.hpp"
#include <Components/GameComponent.hpp>
#include <Rendering/Renderer3D.hpp>

namespace atom
{
    GameObject::GameObject() : parent(nullptr)
    {
    }

    GameObject::~GameObject()
    {
        for (GameComponent* gameComponent : components)
            delete gameComponent;

        for (GameObject* gameObject : children)
            delete gameObject;
    }

    void GameObject::Update()
    {
        for (GameComponent* gameComponent : components)
            gameComponent->Update();

        for (GameObject* gameObject : children)
            gameObject->Update();
    }

    void GameObject::Render(std::shared_ptr<Shader> shader, Renderer3D& renderer3D)
    {
        transform.CalcTransformation();
        
        for (GameComponent* gameComponent : components)
            gameComponent->Render(shader, renderer3D);

        for (GameObject* gameObject : children)
            gameObject->Render(shader, renderer3D);
    }

    std::list<GameObject*> GameObject::GetChildrenRecursively() const
    {
        std::list<GameObject*> allChildren;

        for (GameObject* i : children)
        {
            allChildren.push_back(i);
            std::list<GameObject*> subChildren = i->GetChildrenRecursively();
            allChildren.insert(allChildren.begin(), subChildren.begin(), subChildren.end());
        }

        return allChildren;
    }

    void GameObject::AddChild(GameObject* child)
    {
        child->parent = this;
        child->engine = engine;
        child->transform.parent = &transform;
        children.push_back(child);

        for (GameComponent* component : child->components)
            component->AddToEngine(*engine);
    }

    void GameObject::AddComponent(GameComponent* component)
    {
        component->parent = this;
        components.push_back(component);
    }
}
