#include <iostream>
#include <string>
#include <vector>
#include <memory>

// CREATE A BASE GAME GAMEOBJECT
class GameObject
{
public:
    virtual void Update()
    {
        std::cout << "Updating generic object" << std::endl;
    }

    GameObject()
    {
    }

    virtual ~GameObject()
    {
        std::cout << "Parent Destructor Called" << std::endl;
    }
};

// CREATE A DERIVED CLASS PLAYER

class Player : public GameObject
{
public:
    void Update() override
    {
        std::cout << "Reading Player input : " << std::endl;
    }

    ~Player()
    {
        std::cout << "PLAYER Destructor Called" << std::endl;
    }
};

// CREATE A DERIVED CLASS ENEMY

class EnemyAI : public GameObject
{
public:
    void Update() override
    {
        std::cout << "Calculating Enemy AI... " << std::endl;
    }
    ~EnemyAI()
    {
        std::cout << "ENEMYAI Destructor Called" << std::endl;
    }
};

int main()
{
    std::vector<std::unique_ptr<GameObject>> scene;

    std::unique_ptr<GameObject> player = std::make_unique<Player>();
    std::unique_ptr<GameObject> enemy = std::make_unique<EnemyAI>();

    scene.push_back(std::move(player));
    scene.push_back(std::move(enemy));

    for (auto &item : scene)
    {
        item->Update();
    }
    return 0;
}