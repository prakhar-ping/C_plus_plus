#include <iostream>
#include <unordered_map>
#include <string>

class InventoryManager
{
private:
    std::unordered_map<std::string, int> itemList;

public:
    void AddItem(const std::string &item, const int quantity)
    {
        if (HasItem(item))
        {
            itemList[item] += quantity;
        }
        else
        {
            itemList[item] = quantity;
        }
    }
    bool HasItem(const std::string &item)
    {
        auto val = itemList.find(item);
        if (val != itemList.end())
        {
            return true;
        }
        return false;
    }
    void Print()
    {
        for (const auto &[item, quant] : itemList)
        {
            std::cout << item << " " << quant << std::endl;
        }
    }
};

int main()
{
    InventoryManager inventory;
    inventory.AddItem("Gold", 20);
    inventory.AddItem("Portion", 50);

    inventory.Print();
    inventory.AddItem("Gold", 20);
    inventory.AddItem("Gold", 20);
    inventory.Print();

    return 0;
}