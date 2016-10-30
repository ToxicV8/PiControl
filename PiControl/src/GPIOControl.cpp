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
    if(g_pGpioControl->GetPinValue(pin)){
        g_pGpioControl->SetPinValue(pin, false);
    }else{
        g_pGpioControl->SetPinValue(pin, true);
    }
}

void GPIOControl::HandlerThread()
{
    while(true)
    {
        for(auto p : handlers)
        {
            int pin = p.first;

            ToggleHandler handler = p.second;

            bool state = digitalRead(p.first);

            if(state != states[pin])
            {
                states[pin] = state;
                handler(state);
            }
        }
        delay(20);
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
