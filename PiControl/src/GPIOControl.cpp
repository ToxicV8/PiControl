#include "Includes.h"

GPIOControl::GPIOControl()
{
    //ctor
}

void GPIOControl::Setup()
{

    wiringPiSetup();

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
