#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <chrono>

class EngineThreadPool
{
private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> jobs;

    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;

public:
    // 1. THE CONSTRUCTOR (Spawning the Pool)
    EngineThreadPool(size_t numThreads) : stop(false)
    {
        for (size_t i = 0; i < numThreads; ++i)
        {
            // We give each thread a Lambda function (an anonymous infinite loop)
            workers.push_back(std::thread([this]
                                          {
                while (true) 
                {
                    std::function<void()> job;

                    { // Scope for the lock
                        // std::unique_lock is required for condition_variables (unlike lock_guard)
                        std::unique_lock<std::mutex> lock(this->queueMutex);

                        // SLEEP COMMAND: 
                        // The thread freezes here FOREVER, releasing the lock, UNTIL:
                        // 1. Someone pings the condition variable.
                        // 2. AND either the engine is stopping, OR there is a job in the queue.
                        
                        this->condition.wait(lock, [this] { 
                            return this->stop || !this->jobs.empty(); 
                        });

                        // If the engine is shutting down and the queue is empty, kill the thread.
                        if (this->stop && this->jobs.empty()) {
                            return; 
                        }

                        // Grab the next job in line
                        job = std::move(this->jobs.front());
                        this->jobs.pop();
                    } // Lock is automatically released here so other threads can grab jobs

                    // Execute the job outside the lock! (Massive performance gain)
                    job(); 
                } }));
        }
    }

    // 2. THE SUBMISSION SYSTEM (Giving work to the pool)
    void EnqueueJob(std::function<void()> newJob)
    {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            jobs.push(std::move(newJob)); // Move the job into the queue safely
        }
        // Ping the OS: "Wake up exactly ONE sleeping thread!"
        condition.notify_one();
    }

    // 3. THE DESTRUCTOR (Safe Shutdown)
    ~EngineThreadPool()
    {
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            stop = true; // Flip the kill switch
        }

        // Ping the OS: "Wake up ALL sleeping threads so they can see the kill switch!"
        condition.notify_all();

        // Wait for all threads to finish their current job and terminate
        for (std::thread &worker : workers)
        {
            worker.join();
        }
    }
};
void PrintJob(int jobID)
{
    // Warning: std::cout is not thread-safe and might scramble text if 8 threads print at once!
    // We will ignore the scramble for this test just to prove the threads are firing.
    std::cout << "Executing Job " << jobID << " on thread " << std::this_thread::get_id() << std::endl;
}
int main()
{
    size_t coreCount = std::thread::hardware_concurrency();
    EngineThreadPool pool(coreCount);
    for (int i = 0; i < 50; i++)
    {
        pool.EnqueueJob([i]
                        { PrintJob(i); });
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}