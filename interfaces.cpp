#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

class IDamageable
{
public:
    virtual void ApplyDamage(int amt) = 0;

    virtual ~IDamageable() = default;
};

class BossEnemy : public IDamageable
{
private:
    int armor = 10, health = 100;

public:
    void ApplyDamage(int amt) override
    {
        int damage = std::max(0, amt - armor);
        armor = std::max(0, armor - amt);
        std::cout << "Boss Armor -> " << armor << std::endl;
        if (damage > 0)
        {
            health -= damage;
            std::cout << "Boss took " << damage << " damage. Health: " << health << std::endl;
            if (health <= 0)
                std::cout << "Boss Died!!!!" << std::endl;
        }
    }

    void Taunt()
    {
        std::cout << "Hahaha! Your explosions tickle!" << std::endl;
    }
};

class GlassWindow : public IDamageable
{
public:
    void ApplyDamage(int amt) override
    {
        std::cout << "Window Damaged" << std::endl;
    }
};

int main()
{
    std::vector<std::unique_ptr<IDamageable>> explosiveRadius;
    std::unique_ptr<BossEnemy> boss = std::make_unique<BossEnemy>();
    std::unique_ptr<GlassWindow> window1 = std::make_unique<GlassWindow>();
    std::unique_ptr<GlassWindow> window2 = std::make_unique<GlassWindow>();

    explosiveRadius.push_back(std::move(boss));
    explosiveRadius.push_back(std::move(window1));
    explosiveRadius.push_back(std::move(window2));

    for (const auto &damageables : explosiveRadius)
    {
        damageables->ApplyDamage(50);
        BossEnemy *bossPtr = dynamic_cast<BossEnemy *>(damageables.get());

        if (bossPtr)
        {
            bossPtr->Taunt();
        }

        damageables->ApplyDamage(53);
        damageables->ApplyDamage(60);
    }
    return 0;
}