#ifndef THREADMANAGER_H
#define THREADMANAGER_H

class ThreadManager
{
    public:
        ThreadManager();
        template< class Function, class... Args >
        void RegisterThread(Function&& f, Args&& ... args)
        {
            threads.push_back(std::thread(f, args...));
        }
        void WaitForThreads();
        virtual ~ThreadManager();
    protected:
    private:
    std::vector<std::thread> threads;
};

extern ThreadManager* g_pThreadManager;

#endif // THREADMANAGER_H
