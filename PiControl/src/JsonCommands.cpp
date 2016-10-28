#include "Includes.h"



JsonCommands::JsonCommands()
{


}

void Work(jsoncons::json cmd, int Times)
{
    for(int i = 0; i < Times; i++)
    {
        for(std::string a : cmd.as<std::vector<std::string>>())
        {
            if(a.find("wait ") != std::string::npos){

                std::vector<std::string> arguments;

                g_pHelpers->split(a, ' ', arguments);

                if(arguments.size() > 1)
                {
                    int delay = atoi(arguments.at(1).c_str());

                    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                }


            }else{
                g_pCommandSystem->HandleInput(a);
            }
        }
    }

    g_pLogger->Log("Executed JSON File successfully.");
}

void JsonCommands::Execute(std::string filename)
{

    if(!Error)
    {
        int Times = 1;

        if(j.has_member("Times"))
            Times = j["Times"].as<int>();

        jsoncons::json cmds = j["Commands"];

        g_pThreadManager->RegisterThread(&Work, cmds, Times);
    }
}

std::vector<std::string> JsonCommands::getRequiredKeys()
{
    std::vector<std::string> reqKeys;

    reqKeys.push_back("Commands");

    return reqKeys;
}

JsonCommands::~JsonCommands()
{

}
