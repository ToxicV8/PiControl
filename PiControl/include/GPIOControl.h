#ifndef GPIOCONTROL_H
#define GPIOCONTROL_H


class GPIOControl
{
    public:
        GPIOControl();
        void Setup();
        void SetPullUpDown(int pin, int value);
        void RegisterToggleHandler(int pin, ToggleHandler handler);
        void SetPinValue(int pin, bool value);
        void TogglePin(int pin);
        bool GetPinValue(int pin);
        void HandlerThread();
        virtual ~GPIOControl();
    protected:
    private:
    std::unordered_map<int, bool> states;
    std::unordered_map<int, ToggleHandler> handlers;
};
extern GPIOControl* g_pGpioControl;
#endif // GPIOCONTROL_H
