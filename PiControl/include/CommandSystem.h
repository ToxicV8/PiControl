#ifndef COMMANDSYSTEM_H
#define COMMANDSYSTEM_H

enum DataType
{
    TYPE_INTEGER,
    TYPE_BOOLEAN,
    TYPE_FLOAT,
    TYPE_CALLBACK
};

class CommandSystem
{
    public:
        void AddCommand(const char* cmd_name, void* value, int datatype);
        void AddCallbackCommand(const char* cmd_name, CallbackFunction func);

		// Input Handler
		void HandleInput(std::string input);
private:
	std::vector<Command*> commands;
};

extern CommandSystem* g_pCommandSystem;

#endif // COMMANDSYSTEM_H
