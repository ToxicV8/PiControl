#include "Includes.h"

void CommandSystem::AddCommand(const char* cmd_name, void* value, int datatype)
{
    commands.emplace_back(new Command(cmd_name, value, datatype));
}

void CommandSystem::AddCallbackCommand(const char* cmd_name, CallbackFunction func)
{
    commands.emplace_back(new Command(cmd_name, func));
}

void CommandSystem::HandleInput(std::string input)
{
    transform(input.begin(), input.end(), input.begin(), ::tolower);

    std::vector<std::string> results;

    g_pHelpers->split(input, ' ', results);

    bool validCommand = false;

    if(results.size() > 1)
    {
        for (Command* cmd : commands)
        {
            if (cmd->getName() == results.at(0))
            {
                std::string finalCommand = "";

                for (int i = 1; i < results.size(); i++)
                {
                    finalCommand += results.at(i);
                    if (i < (results.size() - 1))
                    {
                        finalCommand += " ";
                    }
                }

                cmd->Handle(finalCommand);
                validCommand = true;
            }
        }
    }
    else if(results.size() == 1)
    {
        for (Command* cmd : commands)
        {
            if (cmd->getName() == results.at(0))
            {
                validCommand = true;

                if (cmd->getDataType() == TYPE_INTEGER)
                {
                    g_pLogger->Log("%s: %i", cmd->getName().c_str(), *static_cast<int*>(cmd->getValuePointer()));
                }

                if (cmd->getDataType() == TYPE_STRING)
                {
                    g_pLogger->Log("%s: %s", cmd->getName().c_str(), static_cast<std::string*>(cmd->getValuePointer())->c_str());
                }

                if (cmd->getDataType() == TYPE_FLOAT)
                {
                    g_pLogger->Log("%s: %f", cmd->getName().c_str(), *static_cast<float*>(cmd->getValuePointer()));
                }

                if (cmd->getDataType() == TYPE_BOOLEAN)
                {
                    g_pLogger->Log("%s: %s", cmd->getName().c_str(), *static_cast<bool*>(cmd->getValuePointer()) ? "on" : "off");
                }
            }
        }
    }


    if(!validCommand && results.size() > 0)
    {
        std::vector<std::string> similiarCommands;

        for(Command* cmd : commands)
        {
            if(cmd->getName().find(results.at(0)) != std::string::npos)
            {
                similiarCommands.emplace_back(cmd->getName());
            }
        }

        std::string out = "Command " + results.at(0) + " not found!";

        if(similiarCommands.size() > 0)
        {
            out += " Did you mean:";
            for (int i = 0; i < similiarCommands.size(); i++)
            {
                out += " " + similiarCommands.at(i);

                if(i != similiarCommands.size() - 1 )
                {
                    out += ",";
                }
            }
        }
        g_pLogger->Log(out.c_str());

    }
}
