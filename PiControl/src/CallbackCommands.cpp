#include "Includes.h"

CallbackCommands::CallbackCommands()
{
    //ctor
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
    g_pCommandSystem->AddCallbackCommand("getpin", (CallbackFunction)&getpin);
    g_pCommandSystem->AddCallbackCommand("setpin", (CallbackFunction)&setpin);
}


CallbackCommands::~CallbackCommands()
{
    //dtor
}