#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Enemy
{
    int distance, health;

    Enemy(int dist, int HP) : distance(dist), health(HP) {}
};

int main()
{
    vector<Enemy> enemyList;
    Enemy E1(50, 100);
    Enemy E2(20, 50);
    Enemy E3(20, 10);
    Enemy E4(80, 200);
    enemyList.push_back(E1);
    enemyList.push_back(E2);
    enemyList.push_back(E3);
    enemyList.push_back(E4);

    for (const auto &enemy : enemyList)
    {
        cout << enemy.distance << " " << enemy.health << endl;
    }

    sort(enemyList.begin(), enemyList.end(), [](const Enemy &a, const Enemy &b)
         {
            if(a.distance != b.distance)
            {
                return a.distance < b.distance;
            }
            return a.health < b.health; });

    for (const auto &enemy : enemyList)
    {
        cout << enemy.distance << " " << enemy.health << endl;
    }
    // cout << [](int x)
    // { return x + 2; }(2)
    //      << endl;
    // return 0;
}