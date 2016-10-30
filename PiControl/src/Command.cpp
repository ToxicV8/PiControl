#include "Includes.h"

Command::Command(std::string cmd_name, void* valptr, int datatype)
{

    this->m_sCommandName = cmd_name;
    this->valueptr = valptr;
    this->datatype = datatype;
}

Command::Command(std::string cmd_name, CallbackFunction callbackcmd)
{

    this->m_sCommandName = cmd_name;
    this->funct = callbackcmd;
    this->datatype = TYPE_CALLBACK;
}

int Command::getDataType()
{
    return datatype;
}

void* Command::getValuePointer()
{
    return valueptr;
}

std::string Command::getName()
{
    return m_sCommandName;
}

void Command::Handle(std::string input)
{
    std::vector<std::string> results;

	g_pHelpers->split(input, ' ', results);

	std::string val;

	if (results.size() == 0)
		val = input;
	else
		val = results.at(0);

	if (datatype == TYPE_INTEGER)
	{
        int *pInt = static_cast<int*>(valueptr);
		*pInt = atoi(val.c_str());
		g_pLogger->Log("%s is now %i", getName().c_str(), *pInt);
	}

    if(datatype == TYPE_STRING)
    {
        std::string* pString = static_cast<std::string*>(valueptr);

        *pString = input;

        g_pLogger->Log("Set %s to %s", getName().c_str(), pString->c_str());

    }

	if (datatype == TYPE_CALLBACK)
	{
		funct(input);
	}

	if (datatype == TYPE_FLOAT)
	{
        float *pFloat = static_cast<float*>(valueptr);
		*pFloat = atof(val.c_str());
		g_pLogger->Log("%s is now %f", getName().c_str(), *pFloat);
	}

	if (datatype == TYPE_BOOLEAN)
	{
        bool* pBool = static_cast<bool*>(valueptr);

		if (val == "false" || val == "0" || val == "off")
			*pBool = false;
		else
		{
			if (val == "true" || val == "1" || val == "on")
				*pBool = true;
			else
			{
				g_pLogger->Log("Invalid value: %s", val.c_str());
			}
		}
		g_pLogger->Log("%s is now %s", getName().c_str(), *pBool ? "on" : "off");
	}
}

Command::~Command()
{
    //dtor
    //delete valueptr;
}
