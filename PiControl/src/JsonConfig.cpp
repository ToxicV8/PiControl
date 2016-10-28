#include "Includes.h"

JsonConfig::JsonConfig()
{
    //ctor
}

void JsonConfig::ExecuteExport(std::string filename)
{
    if(!Error)
    {
        for(auto a : g_pVariables->vars)
        {
            Var* var = a.second;
            std::string name = a.first;

            switch(var->datatype)
            {
                case TYPE_BOOLEAN:
                    j[name] = var->b;
                    break;
                case TYPE_INTEGER:
                    j[name] = var->i;
                    break;
                case TYPE_FLOAT:
                    j[name] = var->f;
                    break;
                case TYPE_STRING:
                    j[name] = var->s;
                    break;
            }
        }
    }

    //JsonObject::ExecuteExport(filename);
}

void JsonConfig::Execute(std::string filename)
{
    //JsonObject::Execute(filename);

    if(!Error)
    {
        for(auto a : j.members())
        {
            std::unordered_map<std::string, Var*>::const_iterator got = g_pVariables->vars.find(a.name());

            if(got != g_pVariables->vars.end())
            {
                g_pLogger->Log("%s", a.name().c_str());

                Var* v = g_pVariables->vars[a.name()];

                switch(v->datatype)
                {
                    case TYPE_BOOLEAN:
                        v->b = a.value().as<bool>();
                        break;
                    case TYPE_FLOAT:
                        v->f = a.value().as<float>();
                        break;
                    case TYPE_INTEGER:
                        v->i = a.value().as<int>();
                        break;
                    case TYPE_STRING:
                        v->s = a.value().as<std::string>();
                        break;
                }
            }
        }
    }
}

std::vector<std::string> JsonConfig::getRequiredKeys()
{
    std::vector<std::string> RequiredKeys;

    return RequiredKeys;
}

JsonConfig::~JsonConfig()
{
    //dtor
}
