#include "Includes.h"

Helpers::Helpers()
{
    //ctor
}

bool Helpers::stringToBool(std::string str)
{
    if(str == "on" || str == "1" || str == "true")
        return true;

    if(str == "off" || str == "0" || str == "false")
        return false;

    return false;
}

void Helpers::split(const std::string& s, char delim, std::vector<std::string>& elems)
{

	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
}

Helpers::~Helpers()
{
    //dtor
}
