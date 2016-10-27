#ifndef COMMAND_H
#define COMMAND_H


class Command
{
    public:
        //ctors
        Command(std::string cmd_name, void* valptr, int datatype);
        Command(std::string cmd_name, CallbackFunction func);

        // Getters
        std::string getName();
        int getDataType();
        void* getValuePointer();

        // Functions
        void Handle(std::string input);
        // dtors
        virtual ~Command();
    protected:
    private:
        void* valueptr;
        int datatype;
        CallbackFunction funct;
        std::string m_sCommandName;
};

#endif // COMMAND_H
