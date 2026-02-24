#include <iostream>
#include <string>
#include <memory>
#include <vector>

class Adventurer;

class Guild
{
protected:
    std::string name;
    std::vector<std::shared_ptr<Adventurer>> advList;

public:
    Guild(std::string n) : name(n)
    {
        std::cout << "Guild " << name << " Created" << std::endl;
    }

    ~Guild()
    {
        std::cout << "Guild " << name << " Disbanded" << std::endl;
    }
    void AddAdvanturer(std::shared_ptr<Adventurer> adv)
    {
        advList.push_back(adv);
    }
};

class Adventurer
{
protected:
    std::string name;
    std::weak_ptr<Guild> myGuild;

public:
    Adventurer(std::string advName, std::shared_ptr<Guild> guild) : name(advName), myGuild(guild)
    {
        // myGuild->AddAdvanturer();
    }
    ~Adventurer()
    {
        std::cout << name << " has left the game" << std::endl;
    }
};

int main()
{
    std::shared_ptr<Guild> guild = std::make_shared<Guild>("Mages");
    std::shared_ptr<Adventurer> adv1 = std::make_shared<Adventurer>("Merlin", guild);
    std::shared_ptr<Adventurer> adv2 = std::make_shared<Adventurer>("Gandalf", guild);
    guild->AddAdvanturer(adv1);
    guild->AddAdvanturer(adv2);
    std::cout << guild.use_count() << std::endl;
    std::cout << adv1.use_count() << std::endl;
    std::cout << adv2.use_count() << std::endl;
    guild.reset();
    std::cout << guild.use_count() << std::endl;
    std::cout << adv1.use_count() << std::endl;
    std::cout << adv2.use_count() << std::endl;
    return 0;
}