#ifndef LOGGER_H
#define LOGGER_H

class Logger
{
    public:
        Logger();
        void Log(const char* format, ...);
        bool saveLine = true;
        virtual ~Logger();
    protected:
    private:
};

extern Logger* g_pLogger;

#endif // LOGGER_H
