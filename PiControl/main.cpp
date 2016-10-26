#include "Includes.h"


void Handle()
{
    while(true)
    {
        std::string buf;
        std::getline(std::cin, buf);
        g_pCommandSystem->HandleInput(buf);
    }
}

int main()
{

    g_pStarter->Start();

    g_pThreadManager->RegisterThread(&Handle);

    g_pThreadManager->WaitForThreads();

    return 0;
}
