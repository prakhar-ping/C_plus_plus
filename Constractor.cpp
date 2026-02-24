#include<iostream>
#include<string>

class Warrior
{
    private:
    std::string name;
    int health;
    int strength;

    public:

    Warrior(std::string n, int h, int str)
    {
        name = n;
        health = h;
        strength = str;
    }
    
    bool TakeDamage(int damage)
    {
        if(health > 0)
        {
            health -= damage;
        }

        if(health <= 0){
            std::cout<<"Player "<<name<<" DIED!"<<std::endl;
            return false;
        }
        std::cout<<"Player "<<name<<" "<<health<<std::endl;
        return true;
    }

    bool Attack(Warrior &warrior)
    {
        std::cout<<"Player->"<<name<<"->Attached->"<<warrior.name<<std::endl;
        return warrior.TakeDamage(strength);
    }
};

int main()
{
    Warrior w1("p1",100,20);
    Warrior w2("p2",100,10);

    while(true)
    {
        if(!w1.Attack(w2))break;
        if(!w2.Attack(w1))break;
    }
    
}