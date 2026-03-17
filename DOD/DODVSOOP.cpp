#include <iostream>
#include <vector>
#include <chrono>
const int ENTITYSIZE = 1000000;
struct ParticalOOP
{
    float posX = 1, posY = 1, posZ = 1;
    float velX = 1, velY = 1, velZ = 1;
    char padding[64];
};

struct ParticalDOD
{
    std::vector<float> posX, posY, posZ;
    std::vector<float> velX, velY, velZ;
};

int main()
{
    std::vector<ParticalOOP> oopSystem(ENTITYSIZE);
    ParticalDOD dodSystem;
    dodSystem.posX.resize(ENTITYSIZE, 1);
    dodSystem.posY.resize(ENTITYSIZE, 1);
    dodSystem.posZ.resize(ENTITYSIZE, 1);
    dodSystem.velX.resize(ENTITYSIZE, 1);
    dodSystem.velY.resize(ENTITYSIZE, 1);
    dodSystem.velZ.resize(ENTITYSIZE, 1);
    auto start = std::chrono::high_resolution_clock::now();
    for (auto &val : oopSystem)
    {
        val.posX += val.velX;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "OOP Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ENTITYSIZE; i++)
    {
        dodSystem.posX[i] += dodSystem.velX[i];
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    std::cout << "DOD Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count() << "ms\n";
    std::cout << "Verification: " << oopSystem[ENTITYSIZE - 1].posX << " " << dodSystem.posX[ENTITYSIZE - 1] << "\n";
    return 0;
}