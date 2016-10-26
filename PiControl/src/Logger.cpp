#include "Includes.h"

Logger::Logger()
{
    //ctor
}

void Logger::Log(const char* format, ...)
{
  format = (std::string(strdup(format)) + std::string("\n")).c_str();
  va_list args;
  va_start (args, format);
  vprintf (format, args);
  va_end (args);
}

Logger::~Logger()
{
    //dtor
}
