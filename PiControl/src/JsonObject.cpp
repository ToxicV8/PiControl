#include "Includes.h"

JsonObject::JsonObject()
{
    //ctor
}

void JsonObject::Parse(std::string filename)
{
    std::ifstream is(filename, std::ios::in);

    if(is.good() && is.is_open())
    {
        j = jsoncons::json::parse_file(filename);

        for(std::string json : getRequiredKeys())
        {
            if(!j.has_member(json))
            {
                g_pLogger->Log("Error while Parsing %s, one or more required Fields not found.", filename.c_str(), json.c_str());
                Error = true;
            }
        }

    }else
    {
        g_pLogger->Log("Error while Parsing %s, File Stream corrupted.", filename.c_str());
        Error = true;
    }

    is.close();
}


std::vector<std::string> JsonObject::getRequiredKeys()
{
    return std::vector<std::string>();
}

void JsonObject::ExecuteExport(std::string filename)
{

}

void JsonObject::Execute(std::string filename)
{

}

void JsonObject::Write(std::string filename)
{
    std::ofstream os(filename, std::ios::out);

    if(os.good() && os.is_open())
    {
        os << jsoncons::pretty_print(j);
        g_pLogger->Log("Successfully saved JSON to %s.", filename.c_str());
    }else
    {
        g_pLogger->Log("Error while writing to %s, File Stream corrupted.", filename.c_str());
        Error = true;
    }

    os.close();
}

JsonObject::~JsonObject()
{
    //dtor
}
