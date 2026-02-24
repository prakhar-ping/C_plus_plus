#include <iostream>
#include <string>

class Vehicle
{
protected:
    std::string brand;

public:
    Vehicle(std::string b)
    {
        brand = b;
        std::cout << "Vehicle foundation built for: " << brand << std::endl;
    }
};

class Car : public Vehicle
{
private:
    int topSpeed;

public:
    Car(std::string b, int speed) : Vehicle(b)
    {
        brand = b;
        topSpeed = speed;
        std::cout << "Car details added." << std::endl;
    }
    // Add PrintStats() here!
    void PrintStats()
    {
        std::cout << "Top speed = " << topSpeed << std::endl;
        std::cout << "Brand = " << brand << std::endl;
    }
};

int main()
{
    // Create a Car object here (e.g., "Ferrari", 320)
    // Call PrintStats()

    Car car("Ferrari", 320);
    car.PrintStats();
    return 0;
}