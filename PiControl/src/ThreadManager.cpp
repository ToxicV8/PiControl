#include "Includes.h"

ThreadManager::ThreadManager()
{
    threads = std::vector<std::thread>();
}

void ThreadManager::WaitForThreads()
{
    for(auto & thr : threads)
    {
        thr.join();
    }
}

ThreadManager::~ThreadManager()
{
    //dtor
}
