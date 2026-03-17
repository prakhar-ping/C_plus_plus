#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

int backbalance = 0;
std::mutex bankmutex;

void DepositMoney(int amt)
{
    for (int i = 0; i < 10000; i++)
    {
        std::lock_guard<std::mutex> gaurd(bankmutex);
        backbalance += amt;
    }
}

int main()
{
    std::vector<std::thread> worker;
    std::cout << std::thread::hardware_concurrency() << std::endl;
    for (int i = 0; i < 5; i++)
    {
        // std::thread t1(DepositMoney, 1);
        worker.push_back(std::thread(DepositMoney, 1));
    }

    for (auto &t : worker)
    {
        t.join();
    }
    std::cout << "Final balance -> " << backbalance << std::endl;
    std::cout << "Main thread ext stopped." << std::endl;
    return 0;
}