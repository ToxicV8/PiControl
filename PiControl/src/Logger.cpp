#include "Includes.h"

Logger::Logger()
{
    //ctor
}

void Logger::Log(const char* format, ...)
{
    //format = (std::string(strdup(format)) + std::string("\n")).c_str();
    va_list args;
    va_start (args, format);
    std::string final;
    int length;
    va_list apStrLen;
    va_copy(apStrLen, args);
    length = vsnprintf(NULL, 0, format, apStrLen);
    va_end(apStrLen);
    if (length > 0) {
        final.resize(length);
        vsnprintf((char *)final.data(), final.size() + 1, format, args);
    }

    g_pTelegramManager->SendToAllChats(final);
    printf ((final + "\n").c_str());
    va_end (args);
}

Logger::~Logger()
{
    //dtor
}
