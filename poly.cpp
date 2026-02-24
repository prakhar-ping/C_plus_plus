#include<iostream>
#include<string>

class Enemy
{
    public:
    virtual void Speak()
    {
        std::cout<<"Parent"<<std::endl;
    }
};

class Ghost : public Enemy
{
    public:
    void Speak() override
    {
        std::cout<<"Booooo..."<<std::endl;;
    }
};

class Zombie : public Enemy
{
    public:
    void Speak() override
    {
        std::cout<<"Brainnnsss..."<<std::endl;
    }
};

int main()
{
    Enemy* ghost = new Ghost();
    Enemy* Zom= new Zombie();

    ghost->Speak();
    Zom->Speak();
    delete ghost;
    delete Zom;
    return 0;
}