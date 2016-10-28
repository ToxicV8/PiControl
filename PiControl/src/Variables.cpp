#include "Includes.h"

Variables::Variables()
{
    //ctor
}

void Variables::AddVar(std::string name, int defaultval)
{
    vars[name] = new Var(defaultval);

    g_pCommandSystem->AddCommand(name.c_str(), &vars[name]->i, vars[name]->datatype);
}

void Variables::AddVar(std::string name, float defaultval)
{
    vars[name] = new Var(defaultval);

    g_pCommandSystem->AddCommand(name.c_str(), &vars[name]->f, vars[name]->datatype);
}

void Variables::AddVar(std::string name, bool defaultval)
{
    vars[name] = new Var(defaultval);

    g_pCommandSystem->AddCommand(name.c_str(), &vars[name]->b, vars[name]->datatype);
}

void Variables::AddVar(std::string name, std::string defaultval)
{
    vars[name] = new Var(defaultval);

    g_pCommandSystem->AddCommand(name.c_str(), &vars[name]->s, vars[name]->datatype);
}

Variables::~Variables()
{
    //dtor
}
