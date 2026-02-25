#include <iostream>
#include <string>

struct Player
{
    /* data */
    int playerID;
    std::string name;
    Player()
    {
        std::cout << "Constructor called" << std::endl;
    }
};

int main()
{
    int numOfPlayer;
    std::cout << "Enter number of players" << std::endl;
    std::cin >> numOfPlayer;
    Player *playerArr = new Player[numOfPlayer];

    for (int i = 0; i < numOfPlayer; i++)
    {
        std::cout << "Enter Player name " << i + 1 << " data" << std::endl;
        std::cin >> playerArr[i].name;
        std::cout << "Enter Player ID " << i + 1 << " data" << std::endl;
        std::cin >> playerArr[i].playerID;
    }

    for (int i = 0; i < numOfPlayer; i++)
    {
        Player *address = &playerArr[i];
        // std::cout<<"Player "<<i + 1<<" name = "<<playerArr[i].name<<std::endl;
        // std::cout<<"Player "<<i + 1<<" ID = "<<playerArr[i].playerID<<std::endl;

        std::cout << "Player " << i + 1 << " name = " << address->name << std::endl;
        std::cout << "Player " << i + 1 << " ID = " << address->playerID << std::endl;
    }
    delete[] playerArr;
    return 0;
}
