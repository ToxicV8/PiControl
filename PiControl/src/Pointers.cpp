#include "Includes.h"

/*Global Pointers*/
Starter* g_pStarter = new Starter;
Logger* g_pLogger = new Logger;
ThreadManager* g_pThreadManager = new ThreadManager;
Helpers* g_pHelpers = new Helpers;
CommandSystem* g_pCommandSystem = new CommandSystem;
CallbackCommands* g_pCallbackCommands = new CallbackCommands;
GPIOControl* g_pGpioControl = new GPIOControl;
Variables* g_pVariables = new Variables;
TelegramManager* g_pTelegramManager;
TgBot::Bot* g_pBot;
ButtonGame* g_pButtonGame = new ButtonGame;
bool g_bConnected = false;
