#include "Includes.h"

TelegramManager::TelegramManager()
{

}


void TelegramManager::StartAsyncSendRecv()
{
    if(g_pVariables->vars["telegram_token"]->s != "EMPTY")
    {
        TgBot::Bot lbot(g_pVariables->vars["telegram_token"]->s);

        g_pBot = &lbot;

        lbot.getEvents().onAnyMessage([&lbot](TgBot::Message::Ptr message)
        {
            g_pCommandSystem->HandleInput(message->text);
        });

        g_bConnected = true;

        try
        {
            g_pLogger->Log("Telegram Bot started. Bot Username: %s", lbot.getApi().getMe()->username.c_str());
            TgBot::TgLongPoll longPoll(lbot);
            while (true)
            {
                longPoll.start();
            }
        }
        catch (TgBot::TgException& e)
        {
            g_bConnected = false;
            g_pLogger->Log("Error occured while polling Telegram Messages; %s", e.what());
            g_pLogger->Log("Reconnecting to Telegram API!");
            StartAsyncSendRecv();
        }
    }
    else
    {
        g_pLogger->Log("No Telegram Token specified. Not using Telegram!");
    }

}

void TelegramManager::SendToAllChats(std::string message)
{
    try
    {
        if(g_pBot && g_bConnected && g_pVariables->vars["telegram_owner_id"]->i != 0)
        {
            g_pBot->getApi().sendMessage(g_pVariables->vars["telegram_owner_id"]->i, message);
        }
    }
    catch(TgBot::TgException& e)
    {
        g_pLogger->Log("Error while sending Message: %s", e.what());
    }
}


TelegramManager::~TelegramManager()
{
    //dtor
}
