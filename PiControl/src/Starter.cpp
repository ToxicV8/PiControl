#include "Includes.h"

Starter::Starter()
{

}


void Starter::Start()
{
    g_pLogger->Log("Booting PiControl v%i.%i.%i by %s", m_pVersion[0], m_pVersion[1], m_pVersion[2], m_szCoder);

    g_pGpioControl->Setup();

    g_pCallbackCommands->RegisterCommands();

}

Starter::~Starter()
{

}
