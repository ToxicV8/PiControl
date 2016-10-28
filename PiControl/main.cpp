#include "Includes.h"

void History()
{
    char *buf;

    //rl_bind_key('\t',rl_abort);//disable auto-complete

    while((buf = readline(">> "))!=NULL)
    {
        g_pCommandSystem->HandleInput(buf);

        if (buf[0]!=0)
            add_history(buf);
    }

    free(buf);
}

int main()
{

    g_pStarter->Start();

    g_pThreadManager->RegisterThread(&History);

    g_pThreadManager->WaitForThreads();

    return 0;
}
