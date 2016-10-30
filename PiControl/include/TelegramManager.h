#ifndef TELEGRAMMANAGER_H
#define TELEGRAMMANAGER_H


class TelegramManager
{
    public:
        TelegramManager();
        void StartAsyncSendRecv();
        void SendToAllChats(std::string message);
        virtual ~TelegramManager();
        std::string m_sMsg;
    protected:
    private:

};
extern bool g_bConnected;
extern TgBot::Bot* g_pBot;
extern TelegramManager* g_pTelegramManager;
#endif // TELEGRAMMANAGER_H
