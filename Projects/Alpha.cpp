#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <functional>
#include <vector>

class ParticleBuffer
{
private:
    size_t size;
    float *data;

public:
    // Parametrize Constructor
    ParticleBuffer(size_t s) : size(s)
    {
        data = new float[size];

        for (int i = 0; i < size; i++)
            data[i] = 1.0f;
    }

    // Destructor
    ~ParticleBuffer()
    {
        delete[] data;
    }

    // Copy Constructor
    ParticleBuffer(const ParticleBuffer &other)
    {
        size = other.size;
        data = new float[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
        std::cout << "Copy Constructer Completed" << std::endl;
    }

    // Copy assignment operator
    ParticleBuffer &operator=(const ParticleBuffer &other)
    {
        if (this == &other)
        {
            return *this;
        }

        size = other.size;
        delete[] data;
        data = new float[size];

        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
        std::cout << "Copy Assignment Completed" << std::endl;
        return *this;
    }

    // Move Constructor
    ParticleBuffer(ParticleBuffer &&other) noexcept
    {
        size = other.size;
        data = other.data;

        other.size = 0;
        other.data = nullptr;
        std::cout << "Move Constructor Completed" << std::endl;
    }

    // Move assignment operator
    ParticleBuffer &operator=(ParticleBuffer &&other) noexcept
    {
        if (this == &other)
            return *this;

        size = other.size;
        delete[] data;
        data = other.data;

        other.size = 0;
        other.data = nullptr;
        std::cout << "Move Assignment Completed" << std::endl;
        return *this;
    }

    float &operator[](const size_t idx)
    {
        return data[idx];
    }
};

void UpdatePhysicsChunk(ParticleBuffer &posX, ParticleBuffer &velX, int startIndex, int endIndex)
{
    for (int i = startIndex; i < endIndex; i++)
    {
        posX[i] += velX[i];
    }
}

class ThreadPool
{
private:
    std::vector<std::thread> worker;
    std::queue<std::function<void()>> jobs;
    std::mutex queueMutex;
    std::condition_variable c_variable;
    bool stop;

public:
    ThreadPool(size_t count) : stop(false)
    {
        for (int i = 0; i < count; i++)
        {
            worker.push_back(std::thread([this]
                                         {

                while(true)
                {
                    std::function<void()> job;
                    {
                        std::unique_lock<std::mutex> lock(this->queueMutex);
                        this->c_variable.wait(lock, [this]
                            {
                                return this->stop || !this->jobs.empty();
                            });
                        if(this->stop && this->jobs.empty())
                        {
                            return;
                        }
                        job = std::move(this->jobs.front());
                        this->jobs.pop();
                    }
                    job();
                } }));
        }
    }

    void Enqueue(std::function<void()> newJob)
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        jobs.push(newJob);
        c_variable.notify_one();
    }

    ~ThreadPool()
    {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            stop = true;
        }
        c_variable.notify_all();
        for (std::thread &thread : worker)
        {
            thread.join();
        }
    }
};

int main()
{
    ParticleBuffer posX(500000);
    ParticleBuffer velX(500000);
    UpdatePhysicsChunk(posX, velX, 0, 500000);
    std::cout << posX[499999] << std::endl;

    // ThreadPool
    size_t numThreads = std::thread::hardware_concurrency();
    int chunckSize = 500000 / numThreads;
    ThreadPool pool(numThreads);
    for (int i = 0; i < numThreads; i++)
    {

        int start = i * chunckSize;
        int end;
        end = (i + 1) * chunckSize;
        if (i == numThreads - 1)
        {
            end = 500000;
        }

        pool.Enqueue([&posX, &velX, start, end]
                     { UpdatePhysicsChunk(posX, velX, start, end); });
    }
    return 0;
}