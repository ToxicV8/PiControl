#ifndef JSONCONFIG_H
#define JSONCONFIG_H


class JsonConfig : public JsonObject
{
    public:
        JsonConfig();
        void Execute(std::string filename);
        void ExecuteExport(std::string filename);
        std::vector<std::string> getRequiredKeys();
        virtual ~JsonConfig();
    protected:
    private:
};

#endif // JSONCONFIG_H
