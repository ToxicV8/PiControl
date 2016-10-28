#include "Includes.h"

Starter::Starter()
{

}


void Starter::Start()
{
    g_pLogger->Log("Booting PiControl v%i.%i.%i by %s", m_pVersion[0], m_pVersion[1], m_pVersion[2], m_szCoder);

    g_pGpioControl->Setup();

    g_pVariables->AddVar("telegram_token", std::string("EMPTY"));

    g_pCallbackCommands->RegisterCommands();

    g_pCommandSystem->HandleInput("loadconfig default.json");

    g_pTelegramManager = new TelegramManager;

    g_pTelegramManager->StartAsyncSendRecv();

}

Starter::~Starter()
{

}
