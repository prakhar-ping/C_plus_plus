#include <iostream>
#include <string>
#include <memory>

class Weapon
{
    std::string weaponName;

public:
    Weapon(std::string name)
    {
        weaponName = name;
    }
    ~Weapon()
    {
        std::cout << weaponName << "-> has been destroyed" << std::endl;
    }
};

class Chest
{
protected:
    std::unique_ptr<Weapon> lootWeapon = std::make_unique<Weapon>("SMG");

public:
    std::unique_ptr<Weapon> ChestOpen()
    {
        if (lootWeapon != nullptr)
        {
            std::cout << "Chest Open" << std::endl;
            return std::move(lootWeapon);
        }
        else
        {
            std::cout << "Chest is looted" << std::endl;
            return nullptr;
        }
    }
};

class Player
{
protected:
    std::unique_ptr<Weapon> myWeapon;

public:
    void LootChest(Chest &chest)
    {
        std::cout << "&Chest Looted -> " << &chest << std::endl;
        std::unique_ptr<Weapon> loot = chest.ChestOpen();

        if (loot != nullptr)
        {
            myWeapon = std::move(loot);
            std::cout << "Player holding -> " << myWeapon.get() << std::endl;
        }
        else
        {
            std::cout << "Chest is Empty" << std::endl;
        }
    }
};

int main()
{
    std::unique_ptr<Chest> chest = std::make_unique<Chest>();
    std::unique_ptr<Player> player = std::make_unique<Player>();

    player->LootChest(*chest);
    player->LootChest(*chest);

    return 0;
}