#include "Includes.h"

Helpers::Helpers()
{
    //ctor
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
