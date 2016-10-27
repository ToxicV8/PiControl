#ifndef CALLBACKCOMMANDS_H
#define CALLBACKCOMMANDS_H


class CallbackCommands
{
    public:
        CallbackCommands();

        void RegisterCommands();
        virtual ~CallbackCommands();
    protected:
    private:
};
extern CallbackCommands* g_pCallbackCommands;
#endif // CALLBACKCOMMANDS_H
