#include "Includes.h"

Starter::Starter()
{

}

void Async()
{
    g_pTelegramManager->StartAsyncSendRecv();
}

void HandlerThread()
{
    g_pGpioControl->HandlerThread();
}

void Starter::Start()
{
    g_pLogger->Log("Booting PiControl v%i.%i.%i by %s", m_pVersion[0], m_pVersion[1], m_pVersion[2], m_szCoder);

    g_pGpioControl->Setup();

    g_pVariables->AddVar("telegram_token", std::string("EMPTY"));

    g_pVariables->AddVar("telegram_owner_id", 0);

    g_pVariables->AddVar("player1_pin", 1);

    g_pVariables->AddVar("player2_pin", 4);

    g_pVariables->AddVar("led_pin", 7);

    g_pCallbackCommands->RegisterCommands();

    g_pCommandSystem->HandleInput("loadconfig default.json");

    g_pTelegramManager = new TelegramManager;

    g_pThreadManager->RegisterThread(&Async);

    g_pThreadManager->RegisterThread(&HandlerThread);
        //g_pTelegramManager->StartAsyncSendRecv();

}

Starter::~Starter()
{

}
