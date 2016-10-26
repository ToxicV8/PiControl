#ifndef LOGGER_H
#define LOGGER_H

class Logger
{
    public:
        Logger();
        void Log(const char* format, ...);
        virtual ~Logger();
    protected:
    private:
};

extern Logger* g_pLogger;

#endif // LOGGER_H
