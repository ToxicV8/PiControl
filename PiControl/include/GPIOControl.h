#ifndef GPIOCONTROL_H
#define GPIOCONTROL_H


class GPIOControl
{
    public:
        GPIOControl();
        void Setup();
        void SetPinValue(int pin, bool value);
        bool GetPinValue(int pin);
        virtual ~GPIOControl();
    protected:
    private:
};
extern GPIOControl* g_pGpioControl;
#endif // GPIOCONTROL_H
