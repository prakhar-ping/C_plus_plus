#include<iostream>
#include<string>
#include<vector>

int main()
{
    int inventorySize;
    std::vector<std::string> inventory;
    std::string weaponName;
    std::cout<<"Enter number of items in Inventory"<<std::endl;

    std::cin>>inventorySize;
    std::cin.ignore();
    inventory.reserve(inventorySize);
    for(int i = 0; i < inventorySize; i++)
    {
        std::getline(std::cin, weaponName);
        inventory.push_back(weaponName);
    }

    inventory.pop_back();
    // for(int i = 0; i < inventory.size(); i++)
    // {
    //     std::cout<<inventory[i]<<std::endl;
    // }

    for(const auto& item : inventory)
    {
        std::cout<<item<<std::endl;
    }
}