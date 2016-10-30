#include "Includes.h"

GPIOControl::GPIOControl()
{
    //ctor
}

void GPIOControl::Setup()
{
    wiringPiSetup();
}

void GPIOControl::SetPullUpDown(int pin, int value)
{
    pullUpDnControl(pin, value);
}

void GPIOControl::TogglePin(int pin)
{
    if(g_pGpioControl->GetPinValue(pin))
    {
        g_pGpioControl->SetPinValue(pin, false);
    }
    else
    {
        g_pGpioControl->SetPinValue(pin, true);
    }
}

void GPIOControl::HandlerThread()
{
    bool state = false;
    while(true)
    {

        for(auto p : handlers)
        {
            state = digitalRead(p.first);
            if(state != states[p.first])
            {
                states[p.first] = state;
                p.second(state);
            }
        }
        delay(1);
    }
}

void GPIOControl::RegisterToggleHandler(int pin, ToggleHandler handler)
{
    handlers[pin] = handler;
    states[pin] = digitalRead(pin);
}

void GPIOControl::SetPinValue(int pin, bool value)
{
    pinMode(pin, OUTPUT);

    digitalWrite(pin, value ? HIGH : LOW);
}

bool GPIOControl::GetPinValue(int pin)
{
    return digitalRead(pin);
}

GPIOControl::~GPIOControl()
{
    //dtor
}
