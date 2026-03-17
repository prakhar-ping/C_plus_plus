#include <iostream>
#include <memory>
#include <vector>

class Component
{
public:
    virtual void Start()
    {
        std::cout << "Starting generic component." << std::endl;
    }

    virtual ~Component()
    {
    }
};

class PhysicsComponent : public Component
{
public:
    void Start() override
    {
        std::cout << "Initializing Rigidbody." << std::endl;
    }
};

class MeshComponent : public Component
{
public:
    void Start() override
    {
        std::cout << "Loading 3D Model." << std::endl;
    }
};

int main()
{
    std::vector<std::unique_ptr<Component>> components;
    std::unique_ptr<PhysicsComponent> PC = std::make_unique<PhysicsComponent>();
    std::unique_ptr<MeshComponent> MC = std::make_unique<MeshComponent>();

    components.push_back(std::make_unique<PhysicsComponent>());
    components.push_back(std::move(MC));

    for (const auto &range : components)
    {
        range->Start();
    }
    return 0;
}