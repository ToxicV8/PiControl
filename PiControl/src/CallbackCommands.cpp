#include "Includes.h"


CallbackCommands::CallbackCommands()
{
    //ctor
}

void ButtonGame(std::string args)
{
    std::vector<std::string> arguments;

    g_pHelpers->split(args, ' ', arguments);

    if(arguments.size() > 2)
    {
        int rounds = atoi(arguments.at(0).c_str());
        std::string player1 = arguments.at(1);
        std::string player2 = arguments.at(2);

        player1[0] = toupper(player1[0]);
        player2[0] = toupper(player2[0]);

        g_pButtonGame->StartNewGame(rounds, player1, player2);
    }
}


void randomBlink(std::string args)
{
    std::vector<std::string> arguments;

    g_pHelpers->split(args, ' ', arguments);

    if(arguments.size() > 1)
    {
        int pin = atoi(arguments.at(0).c_str());
        int times = atoi(arguments.at(1).c_str());

        for(int i = 0; i < times; i++)
        {
            int delay = rand() % 501;

            if(g_pGpioControl->GetPinValue(pin)){
                g_pGpioControl->SetPinValue(pin, false);
            }else{
                g_pGpioControl->SetPinValue(pin, true);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        }
    }
}


void saveconfig(std::string args)
{
    std::vector<std::string> arguments;

    g_pHelpers->split(args, ' ', arguments);

    if(arguments.size() > 0)
    {
        std::string filename = arguments.at(0);

        JsonConfig conf = JsonConfig();

        conf.ExecuteExport(filename);

        conf.Write(filename);
    }else
    {
        g_pLogger->Log("Usage: saveconfig filename.json");
    }
}

void loadconfig(std::string args)
{
    std::vector<std::string> arguments;

    g_pHelpers->split(args, ' ', arguments);

    if(arguments.size() > 0)
    {
        std::string filename = arguments.at(0);

        JsonConfig conf = JsonConfig();

        conf.Parse(filename);

        conf.Execute(filename);
    }else
    {
        g_pLogger->Log("Usage: loadconfig filename.json");
    }
}

void execjson(std::string args)
{
    std::vector<std::string> arguments;

    g_pHelpers->split(args, ' ', arguments);

    if(arguments.size() > 0)
    {
        std::string filename = arguments.at(0);

        JsonCommands cmd = JsonCommands();

        cmd.Parse(filename);

        cmd.Execute(filename);

    }else
    {
        g_pLogger->Log("Usage: execjson filename.json");
    }
}

void getpin(std::string args)
{
    std::vector<std::string> arguments;

    g_pHelpers->split(args, ' ', arguments);

    if(arguments.size() > 0)
    {
        int pin = atoi(arguments.at(0).c_str());

        bool value = g_pGpioControl->GetPinValue(pin);

        g_pLogger->Log("Pin %i is set to %s", pin, value ? "HIGH" : "LOW");
    }else
    {
        g_pLogger->Log("Usage: getpin pin");
    }

}

void setpin(std::string args)
{
    std::vector<std::string> arguments;

    g_pHelpers->split(args, ' ', arguments);

    if(arguments.size() > 1)
    {
        int pin = atoi(arguments.at(0).c_str());
        bool value = g_pHelpers->stringToBool(arguments.at(1));

        g_pGpioControl->SetPinValue(pin, value);

        g_pLogger->Log("Set Pin %i to %s", pin, value ? "HIGH" : "LOW");

    }else
    {
        g_pLogger->Log("Usage: setpin pin value");
    }

}

void CallbackCommands::RegisterCommands()
{
    g_pCommandSystem->AddCallbackCommand("randomblink", (CallbackFunction)&randomBlink);
    g_pCommandSystem->AddCallbackCommand("saveconfig", (CallbackFunction)&saveconfig);
    g_pCommandSystem->AddCallbackCommand("loadconfig", (CallbackFunction)&loadconfig);
    g_pCommandSystem->AddCallbackCommand("execjson", (CallbackFunction)&execjson);
    g_pCommandSystem->AddCallbackCommand("getpin", (CallbackFunction)&getpin);
    g_pCommandSystem->AddCallbackCommand("setpin", (CallbackFunction)&setpin);
    g_pCommandSystem->AddCallbackCommand("startgame", (CallbackFunction)&ButtonGame);
}


CallbackCommands::~CallbackCommands()
{
    //dtor
}
